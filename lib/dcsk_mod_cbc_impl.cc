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
#include "dcsk_mod_cbc_impl.h"

namespace gr {
  namespace chaos {

    dcsk_mod_cbc::sptr
    dcsk_mod_cbc::make(int n_samples)
    {
      return gnuradio::get_initial_sptr
        (new dcsk_mod_cbc_impl(n_samples));
    }

    /*
     * The private constructor
     */
    dcsk_mod_cbc_impl::dcsk_mod_cbc_impl(int n_samples)
      : gr::block("dcsk_mod_cbc",
                  gr::io_signature::make2(2, 2, sizeof (gr_complex), sizeof (unsigned char)),
                  gr::io_signature::make(1, 1, sizeof(gr_complex))),
        d_n_samples (n_samples)
    {
        set_n_samples(n_samples);
    }

    /*
     * Our virtual destructor.
     */
    dcsk_mod_cbc_impl::~dcsk_mod_cbc_impl()
    {
    }

    void
    dcsk_mod_cbc_impl::set_n_samples (int n_samples)
    {
      if (n_samples < 1) {
           n_samples = 1;
      }

      d_n_samples = n_samples;

      set_relative_rate((double)(2 * n_samples));
      set_output_multiple (2 * n_samples);
    }

    void
    dcsk_mod_cbc_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        int output_bits;

        output_bits = noutput_items / (2 * d_n_samples);
        ninput_items_required[0] = output_bits * d_n_samples;
        ninput_items_required[1] = output_bits;
    }

    // Function that verifies if we have enough chaos samples at the input, bits of data and enough bits available
    // at the output to completly modulate the chaotic signal. The function returns the maximum number
    // of bits that can be computed.
    unsigned int
    dcsk_mod_cbc_impl::verification(unsigned int n_input_chaos,
                                    unsigned int data_bits,
                                    int n_output_items)
    {
        unsigned int chaos_bits, output_bits, n_bits;

        chaos_bits = n_input_chaos / d_n_samples;
        output_bits = n_output_items / (2 * d_n_samples);

        if (chaos_bits < output_bits) {
          if(chaos_bits < data_bits) {
            n_bits = chaos_bits;
          }
          else {
            n_bits = data_bits;
          }
        }
        else {
          if(output_bits < data_bits) {
            n_bits = output_bits;
          }
          else {
            n_bits = data_bits;
          }
        }
        return n_bits;
    }

    int
    dcsk_mod_cbc_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      //unsigned int nchan = input_items.size ();                                                                // total number of inputs (2:chaos,data)
      const gr_complex *in_chaos = (const gr_complex *) input_items[0];                        // chaos input
      const unsigned char *in_data = (const unsigned char *) input_items[1];        // data input
      unsigned int ninput_chaos = ninput_items[0];                                                                // number of chaos samples available
      unsigned int ninput_data = ninput_items[1];                                                                // number of data bits available
      gr_complex *out_signal = (gr_complex *) output_items[0];                                // signal output

      int i,j,nbits_data;
      unsigned int chaos_consumed, out_produced;


      nbits_data = verification(ninput_chaos,ninput_data,noutput_items);

      for(i=0;i<nbits_data;i++)                        // done when all bits are set for the output
        {
          for(j=0;j<d_n_samples;j++)                        // 1 bit for 2*'x' chaos samples
            {
              out_signal[(2*d_n_samples*i)+j] = in_chaos[(d_n_samples*i)+j];                                                // the reference

              if(in_data[i])                                                        // if data=1, data = reference
                {
                  out_signal[((2*d_n_samples*i)+d_n_samples)+j] = in_chaos[(d_n_samples*i)+j];                        // the data
                }
              else                                                                                // if data=0, data = -reference
                {
                  out_signal[((2*d_n_samples*i)+d_n_samples)+j] = (gr_complex) -1 * (in_chaos[(d_n_samples*i)+j]);        // the data
                }
            }
          j=0;
        }
      i=0;

      chaos_consumed = nbits_data*d_n_samples;
      out_produced = nbits_data*(2*d_n_samples);

      consume(0, chaos_consumed);
      consume(1, nbits_data);

      //std::cout << "chaos:" << chaos_consumed << " data:" << nbits_data << " out:" << out_produced << std::endl;

      // Tell runtime system how many output items we produced.
      return out_produced;
    }

  } /* namespace chaos */
} /* namespace gr */

