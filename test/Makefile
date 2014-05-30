CC=gcc

CFLAGS=-g -I../src

LDFAGS=

SOURCE_DIR=../src

SOURCE=$(SOURCE_DIR)/whashtable.c $(SOURCE_DIR)/wlist.c \
	   $(SOURCE_DIR)/wstring.c

all:hashtable


hashtable:hashtable.c
	$(CC) $(CFLAGS) hashtable.c $(SOURCE) -o hashtable

clean:
	rm hashtable
