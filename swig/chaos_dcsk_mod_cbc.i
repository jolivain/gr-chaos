/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access chaos_dcsk_mod_cbc from python as chaos.dcsk_mod_cbc
 */
GR_SWIG_BLOCK_MAGIC(chaos,dcsk_mod_cbc);

chaos_dcsk_mod_cbc_sptr chaos_make_dcsk_mod_cbc (int n_samples);

class chaos_dcsk_mod_cbc : public gr_block
{
private:
  int d_n_samples;
  chaos_dcsk_mod_cbc (int n_samples); 
  unsigned int verification(unsigned int n_input_chaos, 
									 unsigned int data_bits,
								    int n_output_items); 

public:
  int n_samples () const { return d_n_samples; }
  void set_n_samples (int n_samples);
};
