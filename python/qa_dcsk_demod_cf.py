#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2013 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest, blocks, digital
import chaos_swig as chaos

class qa_dcsk_demod_cf (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        chaos_values = (1+0j, 0+1j, -1+0j, 0-1j)
        expected_result = (0, 1, 0, 0, 1, 1)
        zero = chaos_values + tuple(map(lambda v: -v, chaos_values))
        one = 2 * chaos_values
        src_data = zero + one + zero + zero + one + one

        src = blocks.vector_source_c (src_data)
        demod = chaos.dcsk_demod_cf (len(chaos_values), 0)
        slicer = digital.binary_slicer_fb()
        dst = blocks.vector_sink_b ()

        self.tb.connect (src, demod, slicer, dst)

        self.tb.run ()

        result_data = dst.data ()

        self.assertEqual (expected_result, result_data)


if __name__ == '__main__':
    gr_unittest.run(qa_dcsk_demod_cf, "qa_dcsk_demod_cf.xml")
