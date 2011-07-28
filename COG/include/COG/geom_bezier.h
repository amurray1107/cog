namespace cog{
  
  //////////////////////////////
  
  const basic_vector3<F32> bezier_curve
  (int orderu, const basic_vector3<F32> *cpoints, F32 u);
  
  const basic_vector3<F32> bezier_curve_der
  (int orderu, const basic_vector3<F32> *cpoints, F32 u);
  
  const basic_vector3<F32> bezier_patch
  (int orderu, int orderv, const basic_vector3<F32> *cpoints, F32 u, F32 v);
  
  const basic_vector3<F32> bezier_patch_du
  (int orderu, int orderv, const basic_vector3<F32> *cpoints, F32 u, F32 v);
  
  const basic_vector3<F32> bezier_patch_dv
  (int orderu, int orderv, const basic_vector3<F32> *cpoints, F32 u, F32 v);
  
  //////////////////////////////
  
}

