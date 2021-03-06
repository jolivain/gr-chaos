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

#ifndef INCLUDED_CHAOS_DCSK_MOD_CBC_IMPL_H
#define INCLUDED_CHAOS_DCSK_MOD_CBC_IMPL_H

#include <chaos/dcsk_mod_cbc.h>

namespace gr {
  namespace chaos {

    class dcsk_mod_cbc_impl : public dcsk_mod_cbc
    {
     private:
      int d_n_samples;
      unsigned int verification(unsigned int n_input_chaos,
                                unsigned int data_bits,
                                int n_output_items);


     public:
      dcsk_mod_cbc_impl(int n_samples);
      ~dcsk_mod_cbc_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);

      int n_samples () const {
        return (d_n_samples);
      }

      void set_n_samples (int n_samples);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_DCSK_MOD_CBC_IMPL_H */

