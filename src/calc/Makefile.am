bin_PROGRAMS = autocalc
autocalc_SOURCES = main.c

LDADD = \
    $(top_builddir)/src/reader/libreader.la \
    $(top_builddir)/src/parser/libparser.la \
    $(top_builddir)/src/compute/libcompute.la \
    $(top_builddir)/src/mmgr/libmmgr.la

AM_CFLAGS = \
    -I$(top_srcdir)/src/include