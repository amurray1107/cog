namespace cog{
  
  template<typename T>
  class basic_quaternion{
  public:
    typedef T scalar_type;
    
  public:
    inline basic_quaternion()
    {
    }
    
    inline basic_quaternion(const basic_quaternion& q)
    :m_V(q.m_V), m_W(q.m_W)
    {
    }
    
    inline const basic_quaternion& operator=(const basic_quaternion& q)
    {
      m_V = q.m_V, m_W = q.m_W;
      return *this;
    }
    
    inline explicit basic_quaternion(const basic_vector3<T>& v, T w)
    :m_V(v), m_W(w)
    {
    }
    
    const basic_vector3<T>& getV()const{ return m_V; }
    T getW()const{ return m_W; }
    
    ////
    
    const basic_quaternion operator-(void)const
    {
      return basic_quaternion(-m_V, negate(m_W));
    }
    
    const basic_quaternion operator+(const basic_quaternion& q)const
    {
      return basic_quaternion(m_V + q.m_V, add(m_W, q.m_W));
    }
    
    const basic_quaternion operator-(const basic_quaternion& q)const
    {
      return basic_quaternion(m_V - q.m_V, sub(m_W, q.m_W));
    }
    
    const basic_quaternion operator*(T s)const
    {
      return basic_quaternion(m_V * s, mul(m_W, s));
    }
    
    const basic_quaternion operator*(const basic_quaternion& q)const
    {
      const T tw = sub(mul(m_W, q.m_W), dot(m_V, q.m_V));
      const basic_vector3<T> tv ( m_W * q.m_V + m_V * q.m_W );
      return basic_quaternion(tv + cross(m_V, q.m_V), tw);
    }
    
    const basic_vector3<T> operator*(const basic_vector3<T>& p)const
    {
      const basic_vector3<T> cvp = cross(m_V, p);
      const basic_vector3<T> tp = cross(m_V, (cvp + m_W * p));
      return p + const_<T>::two() * tp;
    }
    
  private:
    basic_vector3<T> m_V;
    T m_W;
  };
  
  /////////////
  
  template<typename T>
  inline T dot(const basic_quaternion<T>& a, const basic_quaternion<T>& b)
  {
    return madd(a.getW(), b.getW(), dot(a.getV(), b.getV()));
  }
  
  //
  
  template<typename T>
  inline const basic_quaternion<T> make_quat
  (T radians, const basic_vector3<T>& v)
  {
    const T a = mul(radians, const_<T>::half());
    const T c = cos(a);
    const T s = sin(a);
    return basic_quaternion<T>(v*s, c);
  }
  
  /////////////
  
  template<typename T>
  inline const basic_matrix3<T> make_rotate(const basic_quaternion<T>& q)
  {
    const T qw = q.getW();
    const basic_vector3<T> qv = q.getV();
    const T di = sub(mul(qw, qw), lengthSqr(qv));
    const T x2 = add(qv.getX(), qv.getX());
    const T y2 = add(qv.getY(), qv.getY());
    const T z2 = add(qv.getZ(), qv.getZ());
    const T xx2 = mul(x2, qv.getX());
    const T xy2 = mul(x2, qv.getY());
    const T xz2 = mul(x2, qv.getZ());
    const T xw2 = mul(x2, qw);
    const T yy2 = mul(y2, qv.getY());
    const T yz2 = mul(y2, qv.getZ());
    const T yw2 = mul(y2, qw);
    const T zz2 = mul(z2, qv.getZ());
    const T zw2 = mul(z2, qw);
    
    basic_vector3<T> c0 (add(di, xx2), add(xy2, zw2), sub(xz2, yw2));
    basic_vector3<T> c1 (sub(xy2, zw2), add(di, yy2), add(yz2, xw2));
    basic_vector3<T> c2 (add(xz2, yw2), sub(yz2, xw2), add(di, zz2));
    
    return basic_matrix3<T>(c0, c1, c2);
  }
  
  /////////////
  
  template<typename T>
  inline const basic_quaternion<T> conjugate(const basic_quaternion<T>& q)
  {
    return basic_quaternion<T>(-(q.getV()), q.getW());
  }
  
  template<typename T>
  inline const basic_quaternion<T> inverse(const basic_quaternion<T>& q)
  {
    return conjugate(q) * recip(lengthSqr(q));
  }
  
}

