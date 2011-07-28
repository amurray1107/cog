namespace cog{
  
  //////////////////////////////
  
  const basic_vector3<F32> bezier_curve
  (F32 u0, F32 u1, int orderu, const basic_vector3<F32> *cpoints, F32 u);
  
  const basic_vector3<F32> bezier_patch
  (F32 u0, F32 u1, F32 v0, F32 v1, int orderu, int orderv, 
   const basic_vector3<F32> *cpoints, F32 u, F32 v);
  
  //////////////////////////////
  
}

