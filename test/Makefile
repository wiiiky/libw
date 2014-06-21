CC=gcc

CFLAGS=-g -I../src -pthread

LDFAGS=

SOURCE_DIR=../src

SOURCE=$(SOURCE_DIR)/whashtable.c $(SOURCE_DIR)/wlist.c \
	   $(SOURCE_DIR)/wstring.c $(SOURCE_DIR)/wio.c \
	   $(SOURCE_DIR)/wsort.c $(SOURCE_DIR)/wlog.c \
	   $(SOURCE_DIR)/winet.c $(SOURCE_DIR)/wqueue.c \
	   $(SOURCE_DIR)/wasyncqueue.c $(SOURCE_DIR)/whttp.c

all:hashtable readline readn list sort queue http


hashtable:hashtable.c $(SOURCE)
	$(CC) $(CFLAGS) hashtable.c $(SOURCE) -o hashtable

readline:readline.c $(SOURCE)
	$(CC) $(CFLAGS) readline.c $(SOURCE) -o readline

readn:readn.c $(SOURCE)
	$(CC) $(CFLAGS) readn.c $(SOURCE) -o readn

list:list.c $(SOURCE)
	$(CC) $(CFLAGS) list.c $(SOURCE) -o list

sort:sort.c $(SOURCE)
	$(CC) $(CFLAGS) sort.c $(SOURCE) -o sort

queue:queue.c $(SOURCE)
	$(CC) $(CFLAGS) queue.c $(SOURCE) -o queue

http:http.c $(SOURCE)
	$(CC) $(CFLAGS) http.c $(SOURCE) -o http
 
clean:
	-indent -kr -ts4 -nut *.c
	-rm -f hashtable readline readn list sort queue http *~
