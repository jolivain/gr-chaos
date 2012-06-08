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
#ifndef INCLUDED_CHAOS_LOGMAP_FILTER_FF_H
#define INCLUDED_CHAOS_LOGMAP_FILTER_FF_H

#include <chaos_api.h>
#include <gr_sync_block.h>

class chaos_logmap_filter_ff;

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
typedef boost::shared_ptr<chaos_logmap_filter_ff> chaos_logmap_filter_ff_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of chaos_logmap_filter_ff.
 *
 * To avoid accidental use of raw pointers, chaos_logmap_filter_ff's
 * constructor is private.  chaos_make_logmap_filter_ff is the public
 * interface for creating new instances.
 */
CHAOS_API chaos_logmap_filter_ff_sptr chaos_make_logmap_filter_ff ();

/*!
 * \brief square2 a stream of floats.
 * \ingroup block
 *
 * This uses the preferred technique: subclassing gr_sync_block.
 */
class CHAOS_API chaos_logmap_filter_ff : public gr_sync_block
{
private:
  // The friend declaration allows howto_make_square2_ff to
  // access the private constructor.

  friend CHAOS_API chaos_logmap_filter_ff_sptr chaos_make_logmap_filter_ff ();

  chaos_logmap_filter_ff ();  	// private constructor

 public:
  ~chaos_logmap_filter_ff ();	// public destructor

  // Where all the action really happens

  int work (int noutput_items,
	    gr_vector_const_void_star &input_items,
	    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHAOS_LOGMAP_FILTER_FF_H */
