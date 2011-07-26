namespace cog{

  template<typename T, size_t stride>
  inline const basic_vector3<T> quadratic_bezier_curve
  (const basic_vector3<T> pt[3], T t)
  {
    const T t0 = sub(const_<T>::one(), t);
    const T t1 = t;
    const T t01 = mul(t0, t1);
    
    const basic_vector3<T> v0 = mul(t0, t0) * pt[0*stride];
    const basic_vector3<T> v1 = add(t01, t01) * pt[1*stride];
    const basic_vector3<T> v2 = mul(t1, t1) * pt[2*stride];
    
    return v0 + v1 + v2;
  }
  
  template<typename T, size_t stride>
  inline const basic_vector3<T> cubic_bezier_curve
  (const basic_vector3<T> pt[4], T t)
  {
    const T t0 = sub(const_<T>::one(), t);
    const T t1 = t;
    const T t01 = mul(t0, t1);
    const T t3 = add(t01, add(t01, t01));
    
    const basic_vector3<T> v0 = mul(t0, mul(t0, t0)) * pt[0*stride];
    const basic_vector3<T> v1 = mul(t3, t0) * pt[1*stride];
    const basic_vector3<T> v2 = mul(t3, t1) * pt[2*stride];
    const basic_vector3<T> v3 = mul(t1, mul(t1, t1)) * pt[3*stride];
    
    return v0 + v1 + v2 + v3;
  }

  //////////////////////////////

  template<typename T, size_t stride>
  inline const basic_vector3<T> quadratic_bezier_curve_dt
  (const basic_vector3<T> pt[3], T t)
  {
    const T t0 = sub(const_<T>::one(), t);
    const T t1 = t;

    const basic_vector3<T> d0 = pt[1*stride] - pt[0*stride];
    const basic_vector3<T> d1 = pt[2*stride] - pt[1*stride];

    return add(t0, t0) * d0 + add(t1, t1) * d1;
  }

  template<typename T, size_t stride>
  inline const basic_vector3<T> cubic_bezier_curve_dt
  (const basic_vector3<T> pt[4], T t)
  {
    const T t0 = sub(const_<T>::one(), t);
    const T t1 = t;
    const T t01 = mul(t0, t1);
    
    const T t0s = mul(t0, t0);
    const T t1s = mul(t1, t1);
    const T t0sx3 = add(add(t0s, t0s), t0s);
    const T t1sx3 = add(add(t1s, t1s), t1s);
    const T t01x2 = add(t01, t01);
    const T t01x6 = add(t01x2, add(t01x2, t01x2));
    
    const basic_vector3<T> d0 = pt[1*stride] - pt[0*stride];
    const basic_vector3<T> d1 = pt[2*stride] - pt[1*stride];
    const basic_vector3<T> d2 = pt[3*stride] - pt[2*stride];

    return t0sx3 * d0 + t01x6 * d1 + t1sx3 * d2;
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
    
    const basic_vector3<T> xu0 = quadratic_bezier_curve<T, 1>(pt[0], v);
    const basic_vector3<T> xu1 = quadratic_bezier_curve<T, 1>(pt[1], v);
    const basic_vector3<T> xu2 = quadratic_bezier_curve<T, 1>(pt[2], v);
    
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
    
    const basic_vector3<T> xu0 = cubic_bezier_curve<T, 1>(pt[0], v);
    const basic_vector3<T> xu1 = cubic_bezier_curve<T, 1>(pt[1], v);
    const basic_vector3<T> xu2 = cubic_bezier_curve<T, 1>(pt[2], v);
    const basic_vector3<T> xu3 = cubic_bezier_curve<T, 1>(pt[3], v);
    
    return c0 * xu0 + c1 * xu1 + c2 * xu2 + c3 * xu3;
  }

  //////////////////////////////

  template<typename T>
  inline const basic_vector3<T> quadratic_bezier_patch_du
  (const basic_vector3<T> pt[3][3], T u, T v)
  {
    basic_vector3<T> du0, du1, du2;

    du0 = quadratic_bezier_curve_dt<T, 3>(pt[0]+0, u);
    du1 = quadratic_bezier_curve_dt<T, 3>(pt[0]+1, u);
    du2 = quadratic_bezier_curve_dt<T, 3>(pt[0]+2, u);

    const T v0 = sub(const_<T>::one(), v);
    const T v1 = v;
    const T v01 = mul(v0, v1);
    
    const T c0 = mul(v0, v0);
    const T c1 = add(v01, v01);
    const T c2 = mul(v1, v1);

    return c0 * du0 + c1 * du1 + c2 * du2;
  }

  template<typename T>
  inline const basic_vector3<T> quadratic_bezier_patch_dv
  (const basic_vector3<T> pt[3][3], T u, T v)
  {
    basic_vector3<T> dv0, dv1, dv2;

    dv0 = quadratic_bezier_curve_dt<T, 1>(pt[0], v);
    dv1 = quadratic_bezier_curve_dt<T, 1>(pt[1], v);
    dv2 = quadratic_bezier_curve_dt<T, 1>(pt[2], v);

    const T u0 = sub(const_<T>::one(), u);
    const T u1 = u;
    const T u01 = mul(u0, u1);
    
    const T c0 = mul(u0, u0);
    const T c1 = add(u01, u01);
    const T c2 = mul(u1, u1);

    return c0 * dv0 + c1 * dv1 + c2 * dv2;
  }

  template<typename T>
  inline const basic_vector3<T> cubic_bezier_patch_du
  (const basic_vector3<T> pt[4][4], T u, T v)
  {
    basic_vector3<T> du0, du1, du2, du3;

    du0 = quadratic_bezier_curve_dt<T, 4>(pt[0]+0, u);
    du1 = quadratic_bezier_curve_dt<T, 4>(pt[0]+1, u);
    du2 = quadratic_bezier_curve_dt<T, 4>(pt[0]+2, u);
    du3 = quadratic_bezier_curve_dt<T, 4>(pt[0]+3, u);

    const T v0 = sub(const_<T>::one(), v);
    const T v1 = v;
    const T v01 = mul(v0, v1);
    const T v3 = add(v01, add(v01, v01));
    
    const T c0 = mul(v0, mul(v0, v0));
    const T c1 = mul(v3, v0);
    const T c2 = mul(v3, v1);
    const T c3 = mul(v1, mul(v1, v1));

    return c0 * du0 + c1 * du1 + c2 * du2 + c3 * du3;
  }

  template<typename T>
  inline const basic_vector3<T> cubic_bezier_patch_dv
  (const basic_vector3<T> pt[4][4], T u, T v)
  {
    basic_vector3<T> dv0, dv1, dv2, dv3;

    dv0 = quadratic_bezier_curve_dt<T, 1>(pt[0], v);
    dv1 = quadratic_bezier_curve_dt<T, 1>(pt[1], v);
    dv2 = quadratic_bezier_curve_dt<T, 1>(pt[2], v);
    dv3 = quadratic_bezier_curve_dt<T, 1>(pt[3], v);

    const T u0 = sub(const_<T>::one(), u);
    const T u1 = u;
    const T u01 = mul(u0, u1);
    const T u3 = add(u01, add(u01, u01));
    
    const T c0 = mul(u0, mul(u0, u0));
    const T c1 = mul(u3, u0);
    const T c2 = mul(u3, u1);
    const T c3 = mul(u1, mul(u1, u1));

    return c0 * dv0 + c1 * dv1 + c2 * dv2 + c3 * dv3;
  }

  //////////////////////////////
  
}

