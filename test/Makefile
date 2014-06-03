CC=gcc

CFLAGS=-g -I../src -pthread

LDFAGS=

SOURCE_DIR=../src

SOURCE=$(SOURCE_DIR)/whashtable.c $(SOURCE_DIR)/wlist.c \
	   $(SOURCE_DIR)/wstring.c $(SOURCE_DIR)/wio.c

all:hashtable readline readn


hashtable:hashtable.c $(SOURCE)
	$(CC) $(CFLAGS) hashtable.c $(SOURCE) -o hashtable

readline:readline.c $(SOURCE)
	$(CC) $(CFLAGS) readline.c $(SOURCE) -o readline

readn:readn.c $(SOURCE)
	$(CC) $(CFLAGS) readn.c $(SOURCE) -o readn

clean:
	rm hashtable readline readn
