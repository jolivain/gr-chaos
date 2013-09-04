/* -*- c++ -*- */

#define CHAOS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "chaos_swig_doc.i"

%{
#include "chaos/dcsk_demod_cb.h"
#include "chaos/dcsk_demod_cf.h"
#include "chaos/dcsk_demod_cc.h"
#include "chaos/dcsk_mod_cbc.h"
#include "chaos/gen_logi_map_f.h"
#include "chaos/logmap_filter_ff.h"
%}


%include "chaos/dcsk_demod_cb.h"
GR_SWIG_BLOCK_MAGIC2(chaos, dcsk_demod_cb);
%include "chaos/dcsk_demod_cf.h"
GR_SWIG_BLOCK_MAGIC2(chaos, dcsk_demod_cf);

%include "chaos/dcsk_demod_cc.h"
GR_SWIG_BLOCK_MAGIC2(chaos, dcsk_demod_cc);
%include "chaos/dcsk_mod_cbc.h"
GR_SWIG_BLOCK_MAGIC2(chaos, dcsk_mod_cbc);
%include "chaos/gen_logi_map_f.h"
GR_SWIG_BLOCK_MAGIC2(chaos, gen_logi_map_f);
%include "chaos/logmap_filter_ff.h"
GR_SWIG_BLOCK_MAGIC2(chaos, logmap_filter_ff);
