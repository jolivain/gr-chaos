/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access howto_square_ff from python as chaos.square_ff
 */
GR_SWIG_BLOCK_MAGIC(chaos,gen_logi_map_f);

chaos_gen_logi_map_f_sptr chaos_make_gen_logi_map_f (float seed);

class chaos_gen_logi_map_f : public gr_sync_block
{
private:
  float d_seed;
  float next_val;

  chaos_gen_logi_map_f (float seed); 
  float gen_next_chaos();
  
public:
  float seed () const { return d_seed; }
  void set_seed (float seed) { d_seed = seed; }
};
