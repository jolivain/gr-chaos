/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access chaos from python as chaos.dcsk_demod_cb
 */
GR_SWIG_BLOCK_MAGIC(chaos,dcsk_demod_cb);

chaos_dcsk_demod_cb_sptr chaos_make_dcsk_demod_cb (int n_samples);

class chaos_dcsk_demod_cb : public gr_block
{
private:
  int d_n_samples;
  chaos_dcsk_demod_cb (int n_samples); 

  unsigned int verification(unsigned int n_input_signal,
										       int output_bits);

  cross_corr(const gr_complex * chaos_ref, const gr_complex * chaos_data);

public:
  int n_samples () const { return d_n_samples; }
  void set_n_samples (int n_samples);
};
