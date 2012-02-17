/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access chaos from python as chaos.dcsk_demod_cf
 */
GR_SWIG_BLOCK_MAGIC(chaos,dcsk_demod_cf);

chaos_dcsk_demod_cf_sptr chaos_make_dcsk_demod_cf (int n_samples, int n_sync);

class chaos_dcsk_demod_cf : public gr_block
{
private:
  int d_n_samples;
  int d_n_sync;
  chaos_dcsk_demod_cf (int n_samples, int n_sync); 

  unsigned int verification(unsigned int n_input_signal, int output_bits);

  cross_corr(const gr_complex * chaos_ref, const gr_complex * chaos_data);

public:
  int n_samples () const { return d_n_samples; }
  void set_n_samples (int n_samples);
};
