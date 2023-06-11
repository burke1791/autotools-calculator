lib_LTLIBRARIES = libparser.la

BUILD_SOURCES = calc.tab.h

libparser_la_SOURCES = \
      gram.y \
      scan.l \
      parsetree.c \
      parser.c

AM_YFLAGS = -d

AM_CFLAGS = -I$(srcdir)/include -I$(top_srcdir)/src/include