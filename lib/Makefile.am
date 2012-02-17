#
# Copyright 2004,2005,2006,2008,2009,2010 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

include $(top_srcdir)/Makefile.common

# list of programs run by "make check" and "make distcheck"
TESTS = test_all

# ----------------------------------------------------------------
# chaos C++ library: libgnuradio-chaos.so
# ----------------------------------------------------------------

# C/C++ headers get installed in ${prefix}/include/$(modname)
modinclude_HEADERS = \
	chaos_dcsk_demod_cb.h \
	chaos_dcsk_demod_cf.h \
	chaos_dcsk_demod_cc.h \
	chaos_dcsk_mod_cbc.h \
	chaos_gen_logi_map_f.h \
	chaos_logmap_filter_ff.h

lib_LTLIBRARIES = libgnuradio-chaos.la

libgnuradio_chaos_la_SOURCES = \
	chaos_dcsk_demod_cb.cc \
	chaos_dcsk_demod_cf.cc \
	chaos_dcsk_demod_cc.cc \
	chaos_dcsk_mod_cbc.cc \
	chaos_gen_logi_map_f.cc \
	chaos_logmap_filter_ff.cc

libgnuradio_chaos_la_LIBADD = \
	$(GNURADIO_CORE_LA)

libgnuradio_chaos_la_LDFLAGS = $(NO_UNDEFINED) $(LTVERSIONFLAGS)
