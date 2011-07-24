namespace cog{
  
  template<typename T>
  inline const basic_vector3<T> quadratic_bezier_curve
  (const basic_vector3<T> pt[3], T t)
  {
    const T t0 = sub(const_<T>::one(), t);
    const T t1 = t;
    const T t01 = mul(t0, t1);
    
    const basic_vector3<T> v0 = mul(t0, t0) * pt[0];
    const basic_vector3<T> v1 = add(t01, t01) * pt[1];
    const basic_vector3<T> v2 = mul(t1, t1) * pt[2];
    
    return v0 + v1 + v2;
  }
  
  template<typename T>
  inline const basic_vector3<T> cubic_bezier_curve
  (const basic_vector3<T> pt[4], T t)
  {
    const T t0 = sub(const_<T>::one(), t);
    const T t1 = t;
    const T t01 = mul(t0, t1);
    const T t3 = add(t01, add(t01, t01));
    
    const basic_vector3<T> v0 = mul(t0, mul(t0, t0)) * pt[0];
    const basic_vector3<T> v1 = mul(t3, t0) * pt[1];
    const basic_vector3<T> v2 = mul(t3, t1) * pt[2];
    const basic_vector3<T> v3 = mul(t1, mul(t1, t1)) * pt[3];
    
    return v0 + v1 + v2 + v3;
  }
  
  //////////////////////////////
  
  template<typename T>
  inline const basic_vector3<T> quadratic_bezier_patch
  (const basic_vector3<T> pt[3][3], T u, T v)
  {
    const T u0 = sub(const_<T>::one(), u);
    const T u1 = u;
    const T u01 = mul(u0, u1);
    
    const T c0 = mul(u0, u0);
    const T c1 = add(u01, u01);
    const T c2 = mul(u1, u1);
    
    const basic_vector3<T> xu0 = quadratic_bezier_curve(pt[0], v);
    const basic_vector3<T> xu1 = quadratic_bezier_curve(pt[1], v);
    const basic_vector3<T> xu2 = quadratic_bezier_curve(pt[2], v);
    
    return c0 * xu0 + c1 * xu1 + c2 * xu2;
  }
  
  template<typename T>
  inline const basic_vector3<T> cubic_bezier_patch
  (const basic_vector3<T> pt[4][4], T u, T v)
  {
    const T u0 = sub(const_<T>::one(), u);
    const T u1 = u;
    const T u01 = mul(u0, u1);
    const T u3 = add(u01, add(u01, u01));
    
    const T c0 = mul(u0, mul(u0, u0));
    const T c1 = mul(u3, u0);
    const T c2 = mul(u3, u1);
    const T c3 = mul(u1, mul(u1, u1));
    
    const basic_vector3<T> xu0 = cubic_bezier_curve(pt[0], v);
    const basic_vector3<T> xu1 = cubic_bezier_curve(pt[1], v);
    const basic_vector3<T> xu2 = cubic_bezier_curve(pt[2], v);
    const basic_vector3<T> xu3 = cubic_bezier_curve(pt[3], v);
    
    return c0 * xu0 + c1 * xu1 + c2 * xu2 + c3 * xu3;
  }
  
}

