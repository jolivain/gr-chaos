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


#ifndef INCLUDED_CHAOS_DCSK_DEMOD_CC_H
#define INCLUDED_CHAOS_DCSK_DEMOD_CC_H

#include <chaos/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace chaos {

    /*!
     * \brief <+description of block+>
     * \ingroup chaos
     *
     */
    class CHAOS_API dcsk_demod_cc : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<dcsk_demod_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of chaos::dcsk_demod_cc.
       *
       * To avoid accidental use of raw pointers, chaos::dcsk_demod_cc's
       * constructor is in a private implementation
       * class. chaos::dcsk_demod_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int n_samples, int n_sync);
    };

  } // namespace chaos
} // namespace gr

#endif /* INCLUDED_CHAOS_DCSK_DEMOD_CC_H */

