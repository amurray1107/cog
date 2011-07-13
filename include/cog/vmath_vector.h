namespace cog{
  
  /////////////////////////////
  
  template<typename T>
  class basic_vector3{
  public:
    typedef T scalar_type;
    
  public:
    inline basic_vector3()
    {
    }
    
    inline basic_vector3(const basic_vector3& v)
    :m_X(v.m_X), m_Y(v.m_Y), m_Z(v.m_Z)
    {
    }
    
    inline const basic_vector3& operator=(const basic_vector3& v)
    {
      m_X = v.m_X, m_Y = v.m_Y, m_Z = v.m_Z;
      return *this;
    }
    
    inline explicit basic_vector3(T s)
    :m_X(s), m_Y(s), m_Z(s)
    {
    }
    
    inline explicit basic_vector3(T x, T y, T z)
    :m_X(x), m_Y(y), m_Z(z)
    {
    }
    
    T getX()const{ return m_X; }
    T getY()const{ return m_Y; }
    T getZ()const{ return m_Z; }
    
    inline const basic_vector3 operator-(void)const
    {
      return basic_vector3(negate(getX()), negate(getY()), negate(getZ()));
    }
    
  private:
    T m_X;
    T m_Y;
    T m_Z;
  };
  
  /////////////////////////////
  
  template<typename T>
  class basic_vector4{
  public:
    typedef T scalar_type;
    
  public:
    inline basic_vector4()
    {
    }
    
    inline basic_vector4(const basic_vector4& v)
    :m_X(v.m_X), m_Y(v.m_Y), m_Z(v.m_Z), m_W(v.m_W)
    {
    }
    
    inline const basic_vector4& operator=(const basic_vector4& v)
    {
      m_X = v.m_X, m_Y = v.m_Y, m_Z = v.m_Z, m_W = v.m_W;
      return *this;
    }
    
    inline explicit basic_vector4(T s)
    :m_X(s), m_Y(s), m_Z(s), m_W(s)
    {
    }
    
#ifdef _MSC_VER
    // workaround for compiler bug
    inline explicit basic_vector4(T x, T y, T z, const T& w)
#else
    inline explicit basic_vector4(T x, T y, T z, T w)
#endif
    :m_X(x), m_Y(y), m_Z(z), m_W(w)
    {
    }
    
    T getX()const{ return m_X; }
    T getY()const{ return m_Y; }
    T getZ()const{ return m_Z; }
    T getW()const{ return m_W; }
    
    inline const basic_vector4 operator-(void)const
    {
      return basic_vector4(negate(getX()), negate(getY()), 
                           negate(getZ()), negate(getW()));
    }
    
    ///////
    
    inline explicit basic_vector4(const basic_vector3<T>& v, T w):
    m_X(v.getX()), m_Y(v.getY()), m_Z(v.getZ()), m_W(w)
    {
    }
    
  private:
    T m_X;
    T m_Y;
    T m_Z;
    T m_W;
  };
  
  /////////////////////////////
  
  template<typename T>
  inline const basic_vector3<T> operator+(const basic_vector3<T>& a,
                                          const basic_vector3<T>& b)
  {
    return basic_vector3<T>(add(a.getX(), b.getX()), 
                            add(a.getY(), b.getY()), 
                            add(a.getZ(), b.getZ()));
  }
  
  template<typename T>
  inline const basic_vector3<T> operator-(const basic_vector3<T>& a,
                                          const basic_vector3<T>& b)
  {
    return basic_vector3<T>(sub(a.getX(), b.getX()), 
                            sub(a.getY(), b.getY()), 
                            sub(a.getZ(), b.getZ()));
  }
  
  template<typename T>
  inline const basic_vector3<T> operator*(const basic_vector3<T>& a, T s)
  {
    return basic_vector3<T>(mul(a.getX(), s), 
                            mul(a.getY(), s), 
                            mul(a.getZ(), s));
  }
  
  template<typename T>
  inline const basic_vector3<T> operator*(T s, const basic_vector3<T>& a)
  {
    return a * s;
  }
  
  template<typename T>
  inline const basic_vector4<T> operator+(const basic_vector4<T>& a,
                                          const basic_vector4<T>& b)
  {
    return basic_vector4<T>(add(a.getX(), b.getX()), 
                            add(a.getY(), b.getY()), 
                            add(a.getZ(), b.getZ()), 
                            add(a.getW(), b.getW()));
  }
  
  template<typename T>
  inline const basic_vector4<T> operator-(const basic_vector4<T>& a,
                                          const basic_vector4<T>& b)
  {
    return basic_vector4<T>(sub(a.getX(), b.getX()), 
                            sub(a.getY(), b.getY()), 
                            sub(a.getZ(), b.getZ()), 
                            sub(a.getW(), b.getW()));
  }
  
  template<typename T>
  inline const basic_vector4<T> operator*(const basic_vector4<T>& a, T s)
  {
    return basic_vector4<T>(mul(a.getX(), s), 
                            mul(a.getY(), s), 
                            mul(a.getZ(), s), 
                            mul(a.getW(), s));
  }
  
  template<typename T>
  inline const basic_vector4<T> operator*(T s, const basic_vector4<T>& a)
  {
    return a * s;
  }
  
  /////////////////////////////
  
  template<typename T>
  inline T dot(const basic_vector3<T>& a, const basic_vector3<T>& b)
  {
    T c = mul(a.getX(), b.getX());
    c = madd(a.getY(), b.getY(), c);
    c = madd(a.getZ(), b.getZ(), c);
    return c;
  }
  
  template<typename T>
  inline T dot(const basic_vector4<T>& a, const basic_vector4<T>& b)
  {
    T c = mul(a.getX(), b.getX());
    c = madd(a.getY(), b.getY(), c);
    c = madd(a.getZ(), b.getZ(), c);
    c = madd(a.getW(), b.getW(), c);
    return c;
  }
  
  /////////////////////////////
  
  template<typename T>
  inline const basic_vector3<T> cross(const basic_vector3<T>& v0, 
                                      const basic_vector3<T>& v1)
  {
    T cx = mul(v0.getY(), v1.getZ());
    T cy = mul(v0.getZ(), v1.getX());
    T cz = mul(v0.getX(), v1.getY());
    return basic_vector3<T>(nmsub(v0.getZ(), v1.getY(), cx), 
                            nmsub(v0.getX(), v1.getZ(), cy), 
                            nmsub(v0.getY(), v1.getX(), cz));
  }
  
  /////////////////////////////
  
  template<typename T>
  inline const basic_vector3<T> abs(const basic_vector3<T>& v)
  {
    return basic_vector3<T>(abs(v.getX()), abs(v.getY()), abs(v.getZ()));
  }
  
  template<typename T>
  inline const basic_vector4<T> abs(const basic_vector4<T>& v)
  {
    return basic_vector4<T>(abs(v.getX()), abs(v.getY()), 
                            abs(v.getZ()), abs(v.getW()));
  }
  
  /////////////////////////////
  
  template<typename T>
  inline const basic_vector3<T> min(const basic_vector3<T>& a, 
                                    const basic_vector3<T>& b)
  {
    return basic_vector3<T>(min(a.getX(), b.getX()), 
                            min(a.getY(), b.getY()), 
                            min(a.getZ(), b.getZ()));
  }
  
  template<typename T>
  inline const basic_vector4<T> min(const basic_vector4<T>& a, 
                                    const basic_vector4<T>& b)
  {
    return basic_vector4<T>(min(a.getX(), b.getX()), 
                            min(a.getY(), b.getY()), 
                            min(a.getZ(), b.getZ()),
                            min(a.getW(), b.getW()));
  }
  
  template<typename T>
  inline const basic_vector3<T> max(const basic_vector3<T>& a, 
                                    const basic_vector3<T>& b)
  {
    return basic_vector3<T>(max(a.getX(), b.getX()), 
                            max(a.getY(), b.getY()), 
                            max(a.getZ(), b.getZ()));
  }
  
  template<typename T>
  inline const basic_vector4<T> max(const basic_vector4<T>& a, 
                                    const basic_vector4<T>& b)
  {
    return basic_vector4<T>(max(a.getX(), b.getX()), 
                            max(a.getY(), b.getY()), 
                            max(a.getZ(), b.getZ()),
                            max(a.getW(), b.getW()));
  }
  
  /////////////////////////////
  
  template<typename T>
  inline const basic_vector3<T> reflect
  (const basic_vector3<T>& i, const basic_vector3<T>& n)
  {
    return i - mul(const_<T>::TWO, dot(n,i)) * n;
  }
  
  /////////////////////////////
  
}
