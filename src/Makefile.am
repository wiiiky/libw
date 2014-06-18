## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libwl.la


libwl_la_SOURCES = \
	wlist.c \
	wlog.c \
	wstring.c \
	whashtable.c \
	wio.c \
	winet.c \
	wsort.c \
	wqueue.c

libwl_la_LDFLAGS = 

libwl_la_LIBADD = 



include_HEADERS = \
	libwl.h \
	wlist.h \
	m4.h \
	wlog.h \
	wstring.h \
	whashtable.h \
	wio.h \
	winet.h \
	wsort.h \
	wqueue.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libwl-0.1.pc

EXTRA_DIST = \
	libwl-0.1.pc.in
