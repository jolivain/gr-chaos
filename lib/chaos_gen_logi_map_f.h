/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDED_CHAOS_GEN_LOGI_MAP_F_H
#define INCLUDED_CHAOS_GEN_LOGI_MAP_F_H

#include <gr_sync_block.h>

class chaos_gen_logi_map_f;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr_blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<chaos_gen_logi_map_f> chaos_gen_logi_map_f_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of chaos_gen_logi_map_f.
 *
 * To avoid accidental use of raw pointers, chaos_gen_logi_map_f's
 * constructor is private.  chaos_make_gen_logi_map_f is the public
 * interface for creating new instances.
 */
chaos_gen_logi_map_f_sptr chaos_make_gen_logi_map_f (float seed);

/*!
 * \Generates chaos samples depending on the initial seed
 *
 * This uses the preferred technique: subclassing gr_sync_block.
 */
class chaos_gen_logi_map_f : public gr_sync_block
{
private:
  // The friend declaration allows chaos_make_gen_logi_map_f to
  // access the private constructor.

  friend chaos_gen_logi_map_f_sptr chaos_make_gen_logi_map_f (float seed);

  float d_seed;
  float next_val;
	
  chaos_gen_logi_map_f(float seed);
  float gen_next_chaos();

public:

  float seed() const { return (d_seed); }
  void set_seed(float seed) { d_seed = seed; }

  ~chaos_gen_logi_map_f();

  int work(int noutput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHAOS_GEN_LOGI_MAP_F_H */
