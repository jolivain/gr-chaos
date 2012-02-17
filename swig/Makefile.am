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
include $(top_srcdir)/Makefile.swig

noinst_GUILE  = chaos.test

AM_CPPFLAGS += -I$(top_srcdir)/lib 

###################################
# SWIG interfaces and libraries

TOP_SWIG_IFILES = \
	chaos_swig.i

# Install so that they end up available as:
#   import chaos
# This ends up at:
#   ${prefix}/lib/python${python_version}/site-packages/$(modname)
chaos_swig_pythondir_category = $(modname)

# additional libraries for linking with the SWIG-generated library
chaos_swig_la_swig_libadd = \
	$(top_builddir)/lib/libgnuradio-chaos.la

# additional SWIG files to be installed
chaos_swiginclude_headers = \
	chaos_dcsk_demod_cb.i \
	chaos_dcsk_demod_cf.i \
	chaos_dcsk_demod_cc.i \
	chaos_dcsk_mod_cbc.i \
	chaos_gen_logi_map_f.i \
	chaos_logmap_filter_ff.i

EXTRA_DIST = $(chaos_swiginclude_headers)

if GUILE
TESTS = run_guile_tests
nobase_guile_DATA = \
	gnuradio/chaos_swig.scm
endif

EXTRA_DIST += $(nobase_guile_DATA)
