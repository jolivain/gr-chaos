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
#ifndef INCLUDED_CHAOS_DCSK_DEMOD_CB_H
#define INCLUDED_CHAOS_DCSK_DEMOD_CB_H

#include <chaos_api.h>
#include <gr_block.h>

class chaos_dcsk_demod_cb;

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
typedef boost::shared_ptr<chaos_dcsk_demod_cb> chaos_dcsk_demod_cb_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of chaos_dcsk_demod_cb.
 *
 * To avoid accidental use of raw pointers, chaos_dcsk_demod_cb's
 * constructor is private.  chaos_make_dcsk_demod_cb is the public
 * interface for creating new instances.
 */
CHAOS_API chaos_dcsk_demod_cb_sptr chaos_make_dcsk_demod_cb (int n_samples, int n_sync);

/*!
 * \brief Differential Chaos Shift Keying (DCSK) demodulator.
 *
 * This block implement a demodulation of a chaotic signal modulated
 * using differential chaos shift keying.  The input is complex signal
 * samples.  The output is a bit stream, each bit is encoded on a byte
 * (to be feeded to a deframer).
 *
 * \param n_samples Number of reference chaos samples per symbol (the
 * number of samples for the demodulator must be the same as the
 * modulator).  Be aware that a DCSK symbol is composed of a reference
 * and a data which have the same size.  So each output bit symbol
 * will consume (2 * n_samples) input samples.  Take care when
 * computing the sample rate.
 *
 * \param n_sync Number of sample to search for a better correlation,
 * before and after the current symbol.  The correlation search is
 * optimized and does not fully recompute the cross correlation at
 * each sample.  Each search will compute two complex multiplication,
 * one addition and one substraction.  Setting n_sync to 0 will
 * totally disable the synchronization search.
 *
 * See reference:
 *   G. Kaddoum, J. Olivain, G. Beaufort Samson, P. Giard, F. Gagnon,
 *   "Implementation of a Differential Chaos Shift Keying
 *   Communication system in GNU Radio, International Symposium on
 *   Wireless Communication Systems (ISWCS), August, 2012.
 *
 * \ingroup block
 */
class CHAOS_API chaos_dcsk_demod_cb : public gr_block
{
private:
  friend CHAOS_API chaos_dcsk_demod_cb_sptr
    chaos_make_dcsk_demod_cb (int n_samples,
                              int n_sync);

  int d_n_samples;
  int d_n_sync;

  chaos_dcsk_demod_cb (int n_samples, int n_sync);

  gr_complex cross_corr(const gr_complex * chaos_ref, const gr_complex * chaos_data);


public:

  int n_samples () const {
    return d_n_samples;
  }

  void set_n_samples (int n_samples);

  ~chaos_dcsk_demod_cb ();

  void forecast (int noutput_items, gr_vector_int &ninput_items_required);

  int general_work (int noutput_items,
                    gr_vector_int &ninput_items,
                    gr_vector_const_void_star &input_items,
                    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHAOS_DCSK_DEMOD_CB_H */
