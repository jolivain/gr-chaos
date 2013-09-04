/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "gen_logi_map_f_impl.h"

namespace gr {
  namespace chaos {

    gen_logi_map_f::sptr
    gen_logi_map_f::make(float seed)
    {
      return gnuradio::get_initial_sptr
        (new gen_logi_map_f_impl(seed));
    }

    /*
     * The private constructor
     */
    gen_logi_map_f_impl::gen_logi_map_f_impl(float seed)
      : gr::sync_block("gen_logi_map_f",
                       gr::io_signature::make(0, 0, 0),
                       gr::io_signature::make(1, 1, sizeof(float))),
        d_seed(seed)
    {
      next_val = d_seed;
    }

    /*
     * Our virtual destructor.
     */
    gen_logi_map_f_impl::~gen_logi_map_f_impl()
    {
    }

    float
    gen_logi_map_f_impl::gen_next_chaos()
    {
      float val;

      val = next_val;
      next_val = 1.0 - 2.0 * (val * val);

      return (val);
    }

    int
    gen_logi_map_f_impl::work(int noutput_items,
                              gr_vector_const_void_star &input_items,
                              gr_vector_void_star &output_items)
    {
      float *out_samples = (float *) output_items[0];
      int i;

      for (i = 0; i < noutput_items; i++) {
        out_samples[i] = gen_next_chaos();
      }

      return (noutput_items);
    }

  } /* namespace chaos */
} /* namespace gr */

