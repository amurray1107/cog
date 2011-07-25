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

  //////////////////////////////

  template<typename T>
  inline const basic_vector3<T> cubic_hermite_curve
  (const basic_vector3<T> pt[2], const basic_vector3<T> tangent[2], T t)
  {
    const T ts = mul(t, t);
    const T tc = mul(t, ts);
    const T ts2 = add(ts, ts);
    const T ts3 = add(ts, ts2);
    const T tc2 = add(tc, tc);

    const T c0 = add(sub(tc2, ts3), const_<T>::one());
    const T c1 = add(sub(tc, ts2), t);
    const T c2 = sub(tc, ts);
    const T c3 = sub(ts3, tc2);

    return c0 * pt[0] + c1 * tangent[0] + c2 * tangent[1] + c3 * pt[1];
  }

  template<typename T>
  inline void kochanek_bartels_curve
  (const basic_vector3<T> pt[3], const T tpos[3], 
   T tension, T continuity, T bias, 
   basic_vector3<T>& oInTangent, basic_vector3<T>& oOutTangent )
  {
    const basic_vector3<T> d0 = const_<T>::half() * (pt[1]-pt[0]);
    const basic_vector3<T> d1 = const_<T>::half() * (pt[2]-pt[1]);
    
    const T nt = sub(const_<T>::one(), tension);
    const T pc = add(const_<T>::one(), continuity);
    const T nc = sub(const_<T>::one(), continuity);
    const T pb = add(const_<T>::one(), bias);
    const T nb = sub(const_<T>::one(), bias);

    const T c0 = mul(nt, mul(pc, nb));
    const T c1 = mul(nt, mul(nc, pb));
    const T c2 = mul(nt, mul(nc, nb));
    const T c3 = mul(nt, mul(pc, pb));
    
    const basic_vector3<T> vi = c0 * d1 + c1 * d0;
    const basic_vector3<T> vo = c2 * d1 + c3 * d0;
    const T dt0 = sub(tpos[1], tpos[0]);
    const T dt1 = sub(tpos[2], tpos[1]);
    const T dt01 = add(dt0, dt1);

    oInTangent = vi * div(add(dt1, dt1), dt01);
    oOutTangent = vo *  div(add(dt0, dt0), dt01);
  }
  
}

