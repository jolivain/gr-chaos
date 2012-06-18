/* -*- c++ -*- */
/*
 * Copyright 2004,2010 Free Software Foundation, Inc.
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

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//#define DCSK_DEBUG

#include <chaos_dcsk_demod_cf.h>
#include <gr_io_signature.h>
#include <iostream>
#include <complex>

using namespace std;

/*
 * Create a new instance of chaos_dcsk_demod_cf and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
chaos_dcsk_demod_cf_sptr
chaos_make_dcsk_demod_cf (int n_samples, int n_sync)
{
  return gnuradio::get_initial_sptr(new chaos_dcsk_demod_cf (n_samples, n_sync));
}

/*
 * Specify constraints on number of input and output streams.
 * This info is used to construct the input and output signatures
 * (2nd & 3rd args to gr_block's constructor).  The input and
 * output signatures are used by the runtime system to
 * check that a valid number and type of inputs and outputs
 * are connected to this block.
 */
static const int MIN_IN = 1;    // mininum number of input streams
static const int MAX_IN = 1;    // maximum number of input streams
static const int MIN_OUT = 1;   // minimum number of output streams
static const int MAX_OUT = 1;   // maximum number of output streams

/*
 * The private constructor
 */

chaos_dcsk_demod_cf::chaos_dcsk_demod_cf (int n_samples, int n_sync)
  : gr_block ("dcsk_demod_cf",
              gr_make_io_signature (MIN_IN, MAX_IN, sizeof (gr_complex)),
              gr_make_io_signature (MIN_OUT, MAX_OUT, sizeof (float))),
    d_n_samples (n_samples),
    d_n_sync (n_sync)
{
  set_n_samples(n_samples);
}

/*
 * Our virtual destructor.
 */
chaos_dcsk_demod_cf::~chaos_dcsk_demod_cf ()
{
}

void
chaos_dcsk_demod_cf::set_n_samples (int n_samples)
{
  if (n_samples < 1)
    n_samples = 1;

  d_n_samples = n_samples;

  set_relative_rate(1.0 / (double)(2 * n_samples));
}

void
chaos_dcsk_demod_cf::forecast (int noutput_items,
                               gr_vector_int &ninput_items_required)
{
  ninput_items_required[0] = noutput_items * 2 * d_n_samples;
}

// Makes a cross-correlation of the reference and the data.
gr_complex
chaos_dcsk_demod_cf::cross_corr (const gr_complex * chaos_ref,
                                 const gr_complex * chaos_data)
{
  int i;
  gr_complex correlation(0.0, 0.0);

  for (i = 0; i < d_n_samples; i++)
    correlation += (chaos_ref[i] * conj(chaos_data[i]));

  return correlation;
}


int
chaos_dcsk_demod_cf::general_work (int noutput_items,
                                   gr_vector_int &ninput_items,
                                   gr_vector_const_void_star &input_items,
                                   gr_vector_void_star &output_items)
{
  const unsigned int needed_smp = 2 * d_n_samples + 2 * d_n_sync;
  const gr_complex *in_signal = (const gr_complex *) input_items[0];
  unsigned int ninput_signal = ninput_items[0];
  float *out_info = (float *) output_items[0];
  gr_complex cor(0, 0);
  gr_complex ref(0, 0);
  int out_bits = 0;
  gr_complex best_cor(0.0, 0.0);
  int best_id = 0;
  unsigned int pos = 0;
  int i;

  // Check somewhere that n_sync < n_sample/2

#ifdef DCSK_DEBUG
  cout << "----------------------" << endl;
  cout << "Begin: input samples: " << ninput_signal
       << " output samples: " << noutput_items
       << endl;
#endif

  while ((out_bits < noutput_items) &&
         ((pos + needed_smp) <= ninput_signal)) {

    // Find best correlation, out of d_n_sync * 2 + 1 tries.

    // compute initial correlation
    cor = cross_corr(&in_signal[pos],
                     &in_signal[pos + d_n_samples]);
    best_cor = cor;

#ifdef DCSK_DEBUG
    cout << "loop pos=" << pos << endl;
    cout << "Starting at sample: " << in_signal[pos] << endl;
    cout << "Initial correlation: " << cor << " mag=" << abs(cor) << endl;
#endif

    for (i = 1; i < d_n_sync * 2 + 1; i++) {
      //cor = cross_corr(&in_signal[pos + i],
      //                 &in_signal[pos + i + d_n_samples]);
      // Optimization: instead of recomputing the whole correlation,
      // slide the correlation by one sample to the right:
      // substract the outgoing samples and add the incoming ones.

      cor +=
        ( in_signal[pos + d_n_samples + i] *
          conj(in_signal[pos + 2 * d_n_samples + i]))
        -
        in_signal[pos + i] * conj(in_signal[pos + d_n_samples + i]);

      if (abs(cor) > abs(best_cor)) {
        best_cor = cor;
        best_id = i;
#ifdef DCSK_DEBUG
        cout << "Found best cor=" <<
          abs(best_cor) << " at " << best_id << endl;
#endif
      }
    }

    ref = cross_corr(&in_signal[pos + best_id],
                     &in_signal[pos + best_id]);

    out_info[out_bits] = best_cor.real() / ref.real();

#ifdef DCSK_DEBUG
    cout << "Best offset is " << best_id << " (" <<
      (best_id - d_n_sync) << ")." << endl;
    cout << "Reference auto corr is: " << ref << endl;
    cout << "Output decision is: " << out_info[i] << endl;
#endif

    pos += 2 * d_n_samples + best_id - d_n_sync;
    out_bits++;
  }

#ifdef DCSK_DEBUG
  cout << "Consumed " << pos << " samples" << endl;
  cout << "Produced " << out_bits << " bits" << endl << endl;
#endif

  consume_each(pos);

  return (out_bits);
}
