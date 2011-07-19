namespace cog{
  
  // Generate 3D Transform Matrix
  
  template<typename T>
  inline const basic_matrix3<T> make_rotate
  (T radians, const basic_vector3<T>& axis)
  {
    const T s = sin(radians);
    const T c = cos(radians);
    const T x = axis.getX(), y = axis.getY(), z = axis.getZ();
    const T xy = mul(x, y), yz = mul(y, z), zx = mul(z, x);
    const T omc = sub(const_<T>::ONE, c);
    const basic_vector3<T> c0 (add(mul(mul(x,x), omc), c),
                               add(mul(xy,omc), mul(z,s)),
                               sub(mul(zx,omc), mul(y,s)));
    const basic_vector3<T> c1 (sub(mul(xy,omc), mul(z,s)),
                               add(mul(mul(y,y), omc), c),
                               add(mul(yz,omc), mul(x,s)));
    const basic_vector3<T> c2 (add(mul(zx,omc), mul(y,s)),
                               sub(mul(yz,omc), mul(x,s)),
                               add(mul(mul(z,z), omc), c));
    return basic_matrix3<T>(c0, c1, c2);
  }
  
  template<typename T>
  inline const basic_matrix3<T> make_scale
  (const basic_vector3<T>& scale)
  {
    const T z0 = const_<T>::ZERO;
    const basic_vector3<T> c0 (scale.getX(), z0, z0);
    const basic_vector3<T> c1 (z0, scale.getY(), z0);
    const basic_vector3<T> c2 (z0, z0, scale.getZ());
    return basic_matrix3<T>(c0, c1, c2);
  }
  
  template<typename T>
  inline const basic_matrix3<T> make_rotate
  (const basic_vector3<T>& xaxis, const basic_vector3<T>& yaxis, 
   const basic_vector3<T>& zaxis)
  {
    return transpose(basic_matrix3<T>(xaxis, yaxis, zaxis));
  }
  
  // Projection: 
  
  template<typename T>
  inline const basic_matrix4<T> make_perspective
  (T left, T right, T bottom, T top, T near, T far)
  {
    const T rcp_r_l = recip(sub(right, left));
    const T rcp_t_b = recip(sub(top, bottom));
    const T rcp_n_f = recip(sub(near, far));
    const T ne2 = mul(const_<T>::TWO, near);
    const T z0 = const_<T>::ZERO, n1 = const_<T>::NEONE;
    const T s_r_l = add(right, left);
    const T s_t_b = add(top, bottom);
    const T s_f_n = add(far, near);
    const basic_vector4<T> c0 (mul(ne2, rcp_r_l), z0, z0, z0);
    const basic_vector4<T> c1 (z0, mul(ne2, rcp_t_b), z0, z0);
    const basic_vector4<T> c2 (mul(s_r_l, rcp_r_l),
                               mul(s_t_b, rcp_t_b),
                               mul(s_f_n, rcp_n_f), n1);
    const basic_vector4<T> c3 (z0, z0, mul(mul(far, near), rcp_n_f), z0);
    return basic_matrix4<T>(c0, c1, c2, c3);
  }
  
  template<typename T>
  inline const basic_matrix4<T> make_orthographic
  (T left, T right, T bottom, T top, T near, T far)
  {
    const T rcp_r_l = recip(sub(right, left));
    const T rcp_t_b = recip(sub(top, bottom));
    const T rcp_n_f = recip(sub(near, far));
    const T s_r_l = add(right, left);
    const T s_t_b = add(top, bottom);
    const T s_f_n = add(far, near);
    const T z0 = const_<T>::ZERO, p1 = const_<T>::ONE;
    const basic_vector4<T> c0 (mul(const_<T>::TWO, rcp_r_l), z0, z0, z0);
    const basic_vector4<T> c1 (z0, mul(const_<T>::TWO, rcp_t_b), z0, z0);
    const basic_vector4<T> c2 (z0, z0, mul(const_<T>::TWO, rcp_n_f), z0);
    const basic_vector4<T> c3 (negate(mul(s_r_l, rcp_r_l)),
                               negate(mul(s_t_b, rcp_t_b)),
                               mul(s_f_n, rcp_n_f), p1);
    return basic_matrix4<T>(c0, c1, c2, c3);
  }
  
  // Helper Function: rotate a vector
  
  template<typename T>
  inline const basic_vector3<T> rotate
  (const basic_matrix3<T>& r, const basic_vector3<T>& v)
  {
    return r * v;
  }
  
  template<typename T>
  inline const basic_vector3<T> rotate
  (const basic_matrix4<T>& r, const basic_vector3<T>& v)
  {
    const basic_vector4<T> t = r * basic_vector4<T>(v, const_<T>::ZERO);
    return basic_vector3<T>(t.getX(), t.getY(), t.getZ());
  }
  
  template<typename T>
  inline const basic_vector3<T> rotate
  (const basic_quaternion<T>& r, const basic_vector3<T>& v)
  {
    return r * v;
  }
  
  template<typename T>
  inline const basic_vector3<T> rotate
  (const basic_dualquat<T>& r, const basic_vector3<T>& v)
  {
    return rotate(r.getRotation(), v);
  }
  
  // Helper Function: transform a vector
  
  template<typename T>
  inline const basic_vector3<T> transform
  (const basic_matrix4<T>& tfm, const basic_vector3<T>& v)
  {
    const basic_vector4<T> t = tfm * basic_vector4<T>(v, const_<T>::ONE);
    return basic_vector3<T>(t.getX(), t.getY(), t.getZ());
  }
  
  template<typename T>
  inline const basic_vector3<T> transform
  (const basic_dualquat<T>& tfm, const basic_vector3<T>& v)
  {
    return rotate(tfm.getRotation(), v) + tfm.getDisplacement();
  }
  
}