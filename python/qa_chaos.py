#!/usr/bin/env python
#
# Copyright 2004,2007 Free Software Foundation, Inc.
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

from gnuradio import gr, gr_unittest
import math
import chaos_swig

class qa_chaos (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_chaos_dcsk_mod_cbc (self):
        src_chaos_values = (1+0j, 0+1j, -1+0j, 0-1j)
        src_data_values = (0, 1, 0, 0, 1, 1)
        zero = src_chaos_values + tuple(map(lambda v: -v, src_chaos_values))
        one = 2 * src_chaos_values
        expected_result = zero + one + zero + zero + one + one

        src_chaos = gr.vector_source_c (src_chaos_values * len(src_data_values))
        src_data = gr.vector_source_b (src_data_values)

        chaos_mod = chaos_swig.dcsk_mod_cbc(len(src_chaos_values))

        dst = gr.vector_sink_c ()

        self.tb.connect (src_chaos, (chaos_mod,0))
        self.tb.connect (src_data, (chaos_mod,1))
        self.tb.connect (chaos_mod, dst)

        self.tb.run ()

        result_data = dst.data ()

        self.assertEqual (expected_result, result_data)


    def test_002_chaos_logmap_filter_ff (self):
        src_data = map(lambda x: x/100.0, range(-100, 101))
        expected_result = map(lambda x: math.sin(math.pi / 2.0 * x), src_data)

        src = gr.vector_source_f (src_data)
        dst = gr.vector_sink_f ()

        logmap_filter = chaos_swig.logmap_filter_ff()

        self.tb.connect (src, logmap_filter)
        self.tb.connect (logmap_filter, dst)

        self.tb.run ()

        result_data = dst.data ()

        self.assertFloatTuplesAlmostEqual (expected_result, result_data)


    def test_003_chaos_dcsk_demod_cb (self):
        chaos_values = (1+0j, 0+1j, -1+0j, 0-1j)
        expected_result = (0, 1, 0, 0, 1, 1)
        zero = chaos_values + tuple(map(lambda v: -v, chaos_values))
        one = 2 * chaos_values
        src_data = zero + one + zero + zero + one + one

        src = gr.vector_source_c (src_data)
        demod = chaos_swig.dcsk_demod_cb (len(chaos_values), 0)
        dst = gr.vector_sink_b ()

        self.tb.connect (src, demod)
        self.tb.connect (demod, dst)

        print "start"
        self.tb.run ()

        result_data = dst.data ()

        self.assertFloatTuplesAlmostEqual (expected_result, result_data)


if __name__ == '__main__':
    gr_unittest.main ()
