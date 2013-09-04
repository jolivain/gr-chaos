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

#ifndef INCLUDED_CHAOS_GEN_LOGI_MAP_F_IMPL_H
#define INCLUDED_CHAOS_GEN_LOGI_MAP_F_IMPL_H

#include <chaos/gen_logi_map_f.h>

namespace gr {
  namespace chaos {

    class gen_logi_map_f_impl : public gen_logi_map_f
    {
     private:
      // Nothing to declare in this block.

     public:
      gen_logi_map_f_impl(float seed);
      ~gen_logi_map_f_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_GEN_LOGI_MAP_F_IMPL_H */

