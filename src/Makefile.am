## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libw.la


libw_la_SOURCES = \
	wlist.c \
	wlog.c \
	wstring.c \
	whashtable.c \
	wio.c \
	winet.c \
	wsort.c \
	wasyncqueue.c \
	wqueue.c \
	whttp.c

libw_la_LDFLAGS = 

libw_la_LIBADD = 



include_HEADERS = \
	libw.h \
	wlist.h \
	m4.h \
	wlog.h \
	wstring.h \
	whashtable.h \
	wio.h \
	winet.h \
	wsort.h \
	wasyncqueue.h \
	wqueue.h \
	whttp.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libw-0.1.pc

EXTRA_DIST = \
	libw-0.1.pc.in
