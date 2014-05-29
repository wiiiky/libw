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
	wstring.c

libwl_la_LDFLAGS = 

libwl_la_LIBADD = 



include_HEADERS = \
	libwl.h \
	wlist.h \
	m4.h \
	wlog.h \
	wstring.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libwl-0.1.pc

EXTRA_DIST = \
	libwl-0.1.pc.in
