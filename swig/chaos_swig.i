/* -*- c++ -*- */

%include "gnuradio.i"			// the common stuff

%{
#include "chaos_dcsk_demod_cb.h"
#include "chaos_dcsk_demod_cf.h"
#include "chaos_dcsk_demod_cc.h"
#include "chaos_dcsk_mod_cbc.h"
#include "chaos_gen_logi_map_f.h"
#include "chaos_logmap_filter_ff.h"
%}

%include "chaos_dcsk_demod_cb.i"
%include "chaos_dcsk_demod_cf.i"
%include "chaos_dcsk_demod_cc.i"
%include "chaos_dcsk_mod_cbc.i"
%include "chaos_gen_logi_map_f.i"
%include "chaos_logmap_filter_ff.i"

#if SWIGGUILE
%scheme %{
(load-extension-global "libguile-gnuradio-chaos_swig" "scm_init_gnuradio_chaos_swig_module")
%}

%goops %{
(use-modules (gnuradio gnuradio_core_runtime))
%}
#endif
