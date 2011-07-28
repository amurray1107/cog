#include <COG/vmath_base.h>
#include <COG/vmath_bool.h>
#include <COG/vmath_const.h>
#include <COG/vmath_vector.h>
#include <COG/vmath_const2.h>
#include <COG/geom_bezier.h>

namespace cog{
  
  namespace
  {
    enum{ B_COEFF_MAX_N = 16 };
    const int B_COEFF[B_COEFF_MAX_N][B_COEFF_MAX_N] = {
      { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 4, 6, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 5, 10, 10, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 6, 15, 20, 15, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 7, 21, 35, 35, 21, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 8, 28, 56, 70, 56, 28, 8, 1, 0, 0, 0, 0, 0, 0, 0 }, 
      { 1, 9, 36, 84, 126, 126, 84, 36, 9, 1, 0, 0, 0, 0, 0, 0 }, 
      { 1, 10, 45, 120, 210, 252, 210, 120, 45, 10, 1, 0, 0, 0, 0, 0 }, 
      { 1, 11, 55, 165, 330, 462, 462, 330, 165, 55, 11, 1, 0, 0, 0, 0 }, 
      { 1, 12, 66, 220, 495, 792, 924, 792, 495, 220, 66, 12, 1, 0, 0, 0 }, 
      { 1, 13, 78, 286, 715, 1287, 1716, 1716, 1287, 715, 286, 78, 
        13, 1, 0, 0 }, 
      { 1, 14, 91, 364, 1001, 2002, 3003, 3432, 3003, 2002, 1001, 
        364, 91, 14, 1, 0 }, 
      { 1, 15, 105, 455, 1365, 3003, 5005, 6435, 6435, 5005, 3003, 
        1365, 455, 105, 15, 1 }
    };
    
  }
  
  // order = [degree of polynomial] + 1
  
  template<typename T, typename V>
  inline const V _bezier_curve
  (T u0, T u1, int orderu, const V *cpoints, T u)
  {
    COG_ASSERT(orderu > 0);
    COG_ASSERT(B_COEFF_MAX_N > orderu);
    
    const T uprime = (u-u0)/(u1-u0);
    const T oneMinusX = const_<T>::one() - uprime;
    T XPower = const_<T>::one();
    
    V ret = cpoints[0];
    
    for(int i=1; i<orderu; i++){
      XPower *= uprime;
      ret = oneMinusX * ret + (B_COEFF[orderu-1][i] * XPower) * cpoints[i];
    }
    
    return ret;
  }
  
  template<typename T, typename V>
  inline const V _bezier_patch
  (T u0, T u1, T v0, T v1, int orderu, int orderv, const V *cpoints, T u, T v)
  {
    COG_ASSERT(orderu > 0 && orderv > 0);
    COG_ASSERT(B_COEFF_MAX_N > orderu && B_COEFF_MAX_N > orderv);
    
    const T uprime = (u-u0)/(u1-u0);
    const T oneMinusX = const_<T>::one() - uprime;
    T XPower = const_<T>::one();
    
    V ret = _bezier_curve(v0, v1, orderv, cpoints, v);
    
    for(int i=1; i<orderu; i++){
      cpoints += orderu;
      const V xv = _bezier_curve(v0, v1, orderv, cpoints, v);
      XPower *= uprime;
      ret = oneMinusX * ret + (B_COEFF[orderu-1][i] * XPower) * xv;
    }
    
    return ret;
  }
  
  const basic_vector3<F32> bezier_curve
  (F32 u0, F32 u1, int orderu, const basic_vector3<F32> *cpoints, F32 u)
  {
    return _bezier_curve(u0, u1, orderu, cpoints, u);
  }
  
  const basic_vector3<F32> bezier_patch
  (F32 u0, F32 u1, F32 v0, F32 v1, int orderu, int orderv, 
   const basic_vector3<F32> *cpoints, F32 u, F32 v)
  {
    return _bezier_patch(u0, u1, v0, v1, orderu, orderv, cpoints, u, v);
  }
  
}
