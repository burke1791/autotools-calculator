lib_LTLIBRARIES = libparser.la

BUILT_SOURCES = gram.h

libparser_la_SOURCES = \
      gram.y \
      scan.l \
      parsetree.c \
      parser.c

AM_YFLAGS = -d

AM_CFLAGS = -I$(top_srcdir)/src/include