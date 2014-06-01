/*
 * Copyright (C) 2014  Wiky L
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with main.c; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
#include "wio.h"
#include "m4.h"
#include "wstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>

int w_read(int fd, void *buf, unsigned int count)
{
	int ret;
  AGAIN:
	errno = 0;
	ret = read(fd, buf, count);
	if (ret < 0 && errno == EINTR) {
		goto AGAIN;
	}
	return ret;
}

int w_write(int fd, void *buf, unsigned int count)
{
	int ret;
  AGAIN:
	errno = 0;
	ret = write(fd, buf, count);
	if (ret < 0 && errno == EINTR) {
		goto AGAIN;
	}
	return ret;
}

/************************readline***********************************/
typedef struct {
	unsigned int size;			/* total size */
	unsigned int len;			/* valid buffer size,including \0 */
	char *buf;
} ReadlineBuf;

#define DEFAULT_BUFSIZE (LARGE_BUF)

ReadlineBuf *readline_buf_init()
{
	ReadlineBuf *buf = w_malloc(sizeof(ReadlineBuf));
	buf->size = DEFAULT_BUFSIZE;
	buf->buf = w_malloc(sizeof(char) * DEFAULT_BUFSIZE);
	buf->buf[0] = '\0';
	buf->len = 0;
	return buf;
}

void readline_buf_free(ReadlineBuf * buf)
{
	if (buf == NULL) {
		return;
	}
	w_free(buf->buf);
	w_free(buf);
}

/*
 * move buf forward size bytes
 */
void readline_buf_forward(ReadlineBuf * buf, int size)
{
	if (size <= 0) {
		return;
	} else if (size >= buf->len) {
		buf->len = 0;
		buf->buf[0] = '\0';
		return;
	}
	/* size must be less than buf->len */
	int i, j;
	for (i = size, j = 0; i < buf->len; i++, j++) {
		buf->buf[j] = buf->buf[i];
	}
	buf->buf[buf->len] = '\0';
	buf->len = buf->len - size;
}

void readline_buf_enlarge(ReadlineBuf * buf)
{
	buf->size = buf->size << 1;	/* double */
	buf->buf = w_realloc(buf->buf, buf->size);
}

void readline_buf_make_space(ReadlineBuf * lbuf)
{
	if (lbuf->len >= lbuf->size - 1) {
		readline_buf_enlarge(lbuf);
	}
}


void readline_buf_copydata(ReadlineBuf * lbuf, void *buf,
						   unsigned int count)
{
	strncpy(buf, lbuf->buf, count);
	((char *) buf)[count] = '\0';
	readline_buf_forward(lbuf, count);
}

/*
 * copy a line from ReadlineBuf into buf,
 * return copied size if success,
 * return 0 if fail
 */
int readline_buf_copyline(ReadlineBuf * lbuf, void *buf,
						  unsigned int count)
{
	char *line = strchr(lbuf->buf, '\n');
	if (line == NULL) {
		return 0;
	}
	unsigned int len = line - lbuf->buf + 1;
	unsigned int move = len < count ? len : count - 1;
	readline_buf_copydata(lbuf, buf, move);
	return move;
}


/* Thread-Specific Data */
static pthread_key_t pkey;
static pthread_once_t pkey_once = PTHREAD_ONCE_INIT;

/* 销毁线程专有数据 */
static void pthread_data_destroy(void *ptr)
{
	ReadlineBuf *buf = (ReadlineBuf *) ptr;
	readline_buf_free(buf);
}

static void create_pthread_key(void)
{
	(void) pthread_key_create(&pkey, pthread_data_destroy);
}


int w_readline(int fd, void *buf, unsigned int count)
{
	WL_RETURN_VAL_IF_FAIL(count != 0, 0);

	ReadlineBuf *lbuf = NULL;
	(void) pthread_once(&pkey_once, create_pthread_key);

	if ((lbuf = (ReadlineBuf *) pthread_getspecific(pkey)) == NULL) {
		/* the first time */
		lbuf = readline_buf_init();
		(void) pthread_setspecific(pkey, lbuf);
	}
	int rd;
	if ((rd = readline_buf_copyline(lbuf, buf, count)) > 0) {
		return rd;
	}

	readline_buf_make_space(lbuf);
	rd = 0;
	while ((rd =
			w_read(fd, lbuf->buf + lbuf->len,
				   lbuf->size - lbuf->len)) > 0) {
		if (rd == 0) {
			/* EOF */
			unsigned int move = lbuf->len < count ? lbuf->len : count - 1;
			readline_buf_copydata(lbuf, buf, move);
			return move;
		}
		lbuf->len += rd;
		lbuf->buf[lbuf->len] = '\0';
		if ((rd = readline_buf_copyline(lbuf, buf, count)) > 0) {
			return rd;
		}
		readline_buf_make_space(lbuf);
	}
	return rd;
}
