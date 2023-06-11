bin_PROGRAMS = autocalc
autocalc_SOURCES = main.c

LDADD = \
    $(top_builddir)/src/reader/libreader.la \
    $(top_builddir)/src/parser/libparser.la

AM_CFLAGS = \
    -I$(top_srcdir)/src/reader/include \
    -I$(top_srcdir)/src/parser/include \
    -I$(top_srcdir)/src/include