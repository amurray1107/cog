namespace cog{
  
  /////////////////////////////
  
  template<typename T>
  class basic_matrix3{
  public:
    typedef T scalar_type;
    
  public:
    inline basic_matrix3()
    {
    }
    
    inline basic_matrix3(const basic_matrix3& m)
    :m_C0(m.m_C0), m_C1(m.m_C1), m_C2(m.m_C2)
    {
    }
    
    inline const basic_matrix3& operator=(const basic_matrix3& m)
    {
      m_C0 = m.m_C0, m_C1 = m.m_C1, m_C2 = m.m_C2;
      return *this;
    }
    
    inline explicit basic_matrix3(T s)
    :m_C0(s), m_C1(s), m_C2(s)
    {
    }
    
    inline explicit basic_matrix3(const basic_vector3<T>& v0, 
                                  const basic_vector3<T>& v1, 
                                  const basic_vector3<T>& v2 )
    :m_C0(v0), m_C1(v1), m_C2(v2)
    {
    }
    
    const basic_vector3<T>& getColumn0()const{ return m_C0; }
    const basic_vector3<T>& getColumn1()const{ return m_C1; }
    const basic_vector3<T>& getColumn2()const{ return m_C2; }
    
    const basic_matrix3 operator-(void)const
    {
      return basic_matrix3(-m_C0, -m_C1, -m_C2);
    }
    
    const basic_matrix3 operator+(const basic_matrix3& m)const
    {
      return basic_matrix3(m_C0 + m.m_C0, m_C1 + m.m_C1, m_C2 + m.m_C2);
    }
    
    const basic_matrix3 operator-(const basic_matrix3& m)const
    {
      return basic_matrix3(m_C0 - m.m_C0, m_C1 - m.m_C1, m_C2 - m.m_C2);
    }
    
    const basic_matrix3 operator*(T s)const
    {
      return basic_matrix3(m_C0 * s, m_C1 * s, m_C2 * s);
    }
    
    const basic_vector3<T> operator*(const basic_vector3<T>& v)const
    {
      return m_C0*v.getX() + m_C1*v.getY() + m_C2*v.getZ();
    }
    
    const basic_matrix3 operator*(const basic_matrix3& m)const
    {
      const basic_matrix3& me = *this;
      return basic_matrix3(me*m.m_C0, me*m.m_C1, me*m.m_C2);
    }
    
    ////////
    
    
    
  private:
    basic_vector3<T> m_C0;
    basic_vector3<T> m_C1;
    basic_vector3<T> m_C2;
  };
  
  /////////////////////////////
  
  template<typename T>
  class basic_matrix4{
  public:
    typedef T scalar_type;
    
  public:
    inline basic_matrix4()
    {
    }
    
    inline basic_matrix4(const basic_matrix4& m)
    :m_C0(m.m_C0), m_C1(m.m_C1), m_C2(m.m_C2), m_C3(m.m_C3)
    {
    }
    
    inline const basic_matrix4& operator=(const basic_matrix4& m)
    {
      m_C0 = m.m_C0, m_C1 = m.m_C1, m_C2 = m.m_C2, m_C3 = m.m_C3;
      return *this;
    }
    
    inline explicit basic_matrix4(T s)
    :m_C0(s), m_C1(s), m_C2(s), m_C3(s)
    {
    }
    
    inline explicit basic_matrix4(const basic_vector4<T>& v0, 
                                  const basic_vector4<T>& v1, 
                                  const basic_vector4<T>& v2,
                                  const basic_vector4<T>& v3 )
    :m_C0(v0), m_C1(v1), m_C2(v2), m_C3(v3)
    {
    }
    
    const basic_vector4<T>& getColumn0()const{ return m_C0; }
    const basic_vector4<T>& getColumn1()const{ return m_C1; }
    const basic_vector4<T>& getColumn2()const{ return m_C2; }
    const basic_vector4<T>& getColumn3()const{ return m_C3; }
    
    const basic_matrix4 operator-(void)const
    {
      return basic_matrix4(-m_C0, -m_C1, -m_C2, -m_C3);
    }
    
    const basic_matrix4 operator+(const basic_matrix4& m)const
    {
      return basic_matrix4(m_C0 + m.m_C0, m_C1 + m.m_C1, 
                           m_C2 + m.m_C2, m_C3 + m.m_C3);
    }
    
    const basic_matrix4 operator-(const basic_matrix4& m)const
    {
      return basic_matrix4(m_C0 - m.m_C0, m_C1 - m.m_C1, 
                           m_C2 - m.m_C2, m_C3 - m.m_C3);
    }
    
    const basic_matrix4 operator*(T s)const
    {
      return basic_matrix4(m_C0 * s, m_C1 * s, m_C2 * s, m_C3 * s);
    }
    
    const basic_vector4<T> operator*(const basic_vector4<T>& v)const
    {
      return m_C0*v.getX() + m_C1*v.getY() + m_C2*v.getZ() + m_C3*v.getW();
    }
    
    const basic_matrix4 operator*(const basic_matrix4& m)const
    {
      const basic_matrix4& me = *this;
      return basic_matrix4(me*m.m_C0, me*m.m_C1, me*m.m_C2, me*m.m_C3);
    }
    
    ///////
    
    explicit basic_matrix4
    (const basic_matrix3<T>& m, const basic_vector3<T>& t):
    m_C0(m.getColumn0(), 0.0f), m_C1(m.getColumn1(), 0.0f), 
    m_C2(m.getColumn2(), 0.0f), m_C3(t, 1.0f)
    {
    }
    
  private:
    basic_vector4<T> m_C0;
    basic_vector4<T> m_C1;
    basic_vector4<T> m_C2;
    basic_vector4<T> m_C3;
  };
  
  /////////////////////////////
  
  template<typename T>
  inline const basic_matrix3<T> transpose(const basic_matrix3<T>& m)
  {
    const basic_vector3<T> c0 = m.getColumn0();
    const basic_vector3<T> c1 = m.getColumn1();
    const basic_vector3<T> c2 = m.getColumn2();
    const basic_vector3<T> r0 (c0.getX(), c1.getX(), c2.getX());
    const basic_vector3<T> r1 (c0.getY(), c1.getY(), c2.getY());
    const basic_vector3<T> r2 (c0.getZ(), c1.getZ(), c2.getZ());
    return basic_matrix3<T>(r0, r1, r2);
  }
  
  template<typename T>
  inline const basic_matrix4<T> transpose(const basic_matrix4<T>& m)
  {
    const basic_vector4<T> c0 = m.getColumn0();
    const basic_vector4<T> c1 = m.getColumn1();
    const basic_vector4<T> c2 = m.getColumn2();
    const basic_vector4<T> c3 = m.getColumn3();
    const basic_vector4<T> r0 (c0.getX(), c1.getX(), c2.getX(), c3.getX());
    const basic_vector4<T> r1 (c0.getY(), c1.getY(), c2.getY(), c3.getY());
    const basic_vector4<T> r2 (c0.getZ(), c1.getZ(), c2.getZ(), c3.getZ());
    const basic_vector4<T> r3 (c0.getW(), c1.getW(), c2.getW(), c3.getW());
    return basic_matrix4<T>(r0, r1, r2, r3);
  }
  
  /////////////////////////////
  
  template<typename T>
  inline const basic_matrix3<T> inverse_transposed(const basic_matrix3<T>& m)
  {
    const basic_vector3<T> tmp0 = cross(m.getColumn1(), m.getColumn2());
    const basic_vector3<T> tmp1 = cross(m.getColumn2(), m.getColumn0());
    const basic_vector3<T> tmp2 = cross(m.getColumn0(), m.getColumn1());
    const T detinv = recip(dot(m.getColumn2(), tmp2));
    return basic_matrix3<T>(tmp0, tmp1, tmp2) * detinv;
  }
  
  template<typename T>
  inline const basic_matrix3<T> inverse(const basic_matrix3<T>& m)
  {
    return transpose(inverse_transposed(m));
  }
  
  /////////////////////////////
  
}
