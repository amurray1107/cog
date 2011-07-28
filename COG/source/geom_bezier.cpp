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
  (int orderu, const V *cpoints, T u, size_t stride)
  {
    COG_ASSERT(orderu > 0);
    COG_ASSERT(B_COEFF_MAX_N > orderu);
    
    const T X = u;
    const T oneMinusX = const_<T>::one() - X;
    T XPower = const_<T>::one();
    
    V ret = cpoints[0];
    
    for(int i=1; i<orderu; i++){
      cpoints += stride;
      XPower *= X;
      ret = oneMinusX * ret + (B_COEFF[orderu-1][i] * XPower) * (*cpoints);
    }
    
    return ret;
  }
  
  template<typename T, typename V>
  inline const V _bezier_patch
  (int orderu, int orderv, const V *cpoints, T u, T v)
  {
    COG_ASSERT(orderu > 0 && orderv > 0);
    COG_ASSERT(B_COEFF_MAX_N > orderu && B_COEFF_MAX_N > orderv);
    
    const T X = u;
    const T oneMinusX = const_<T>::one() - X;
    T XPower = const_<T>::one();
    
    V ret = _bezier_curve(orderv, cpoints, v, 1);
    
    for(int i=1; i<orderu; i++){
      cpoints += orderv;
      XPower *= X;
      const V xv = _bezier_curve(orderv, cpoints, v, 1);
      ret = oneMinusX * ret + (B_COEFF[orderu-1][i] * XPower) * xv;
    }
    
    return ret;
  }
  
  /////////////////////////////////////////////////////////////////////////////
  
  template<typename T, typename V>
  inline const V _bezier_curve_der
  (int orderu, const V *cpoints, T u, size_t stride)
  {
    COG_ASSERT(orderu > 1);
    COG_ASSERT(B_COEFF_MAX_N > orderu);
    
    const T X = u;
    const T oneMinusX = const_<T>::one() - X;
    T XPower = const_<T>::one();
    
    V ret = cpoints[stride] - cpoints[0];
    
    for(int i=1; i<orderu-1; i++){
      cpoints += stride;
      XPower *= X;
      const V dv = *(cpoints+stride) - *(cpoints);
      ret = oneMinusX * ret + (B_COEFF[orderu-2][i] * XPower) * dv;
    }
    
    return T(orderu-1) * ret;
  }
  
  template<typename T, typename V>
  inline const V _bezier_patch_dv
  (int orderu, int orderv, const V *cpoints, T u, T v)
  {
    COG_ASSERT(orderu > 1 && orderv > 1);
    COG_ASSERT(B_COEFF_MAX_N > orderu && B_COEFF_MAX_N > orderv);
    
    const T X = u;
    const T oneMinusX = const_<T>::one() - X;
    T XPower = const_<T>::one();
    
    V ret = _bezier_curve_der(orderv, cpoints, v, 1);
    
    for(int i=1; i<orderu; i++){
      cpoints += orderv;
      XPower *= X;
      const V dv = _bezier_curve_der(orderv, cpoints, v, 1);
      ret = oneMinusX * ret + (B_COEFF[orderu-1][i] * XPower) * dv;
    }
    
    return ret;
  }
  
  template<typename T, typename V>
  inline const V _bezier_patch_du
  (int orderu, int orderv, const V *cpoints, T u, T v)
  {
    COG_ASSERT(orderu > 1 && orderv > 1);
    COG_ASSERT(B_COEFF_MAX_N > orderu && B_COEFF_MAX_N > orderv);
    
    const T X = u;
    const T oneMinusX = const_<T>::one() - X;
    T XPower = const_<T>::one();
    
    V oret = _bezier_curve(orderv, cpoints+orderv, v, 1);
    V ret = oret - _bezier_curve(orderv, cpoints, v, 1);
    
    for(int i=1; i<orderu-1; i++){
      cpoints += orderv;
      XPower *= X;
      V pret = _bezier_curve(orderv, cpoints+orderv, v, 1);
      ret = oneMinusX * ret + (B_COEFF[orderu-2][i] * XPower) * (pret-oret);
      oret = pret;
    }
    
    return T(orderu-1) * ret;
  }
  
  /////////////////////////////////////////////////////////////////////////////

  const basic_vector3<F32> bezier_curve
  (int orderu, const basic_vector3<F32> *cpoints, F32 u)
  {
    return _bezier_curve(orderu, cpoints, u, 1);
  }
  
  const basic_vector3<F32> bezier_curve_der
  (int orderu, const basic_vector3<F32> *cpoints, F32 u)
  {
    return _bezier_curve_der(orderu, cpoints, u, 1);
  }
  
  const basic_vector3<F32> bezier_patch
  (int orderu, int orderv, const basic_vector3<F32> *cpoints, F32 u, F32 v)
  {
    return _bezier_patch(orderu, orderv, cpoints, u, v);
  }
  
  const basic_vector3<F32> bezier_patch_dv
  (int orderu, int orderv, const basic_vector3<F32> *cpoints, F32 u, F32 v)
  {
    return _bezier_patch_dv(orderu, orderv, cpoints, u, v);
  }
  
  const basic_vector3<F32> bezier_patch_du
  (int orderu, int orderv, const basic_vector3<F32> *cpoints, F32 u, F32 v)
  {
    return _bezier_patch_du(orderu, orderv, cpoints, u, v);
  }
  
}
