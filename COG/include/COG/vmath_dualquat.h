namespace cog{
  
  template<typename T>
  class basic_dualquat{
  public:
    typedef T scalar_type;
    
  public:
    inline basic_dualquat()
    {
    }
    
    inline basic_dualquat(const basic_dualquat& dq)
    :m_Q0(dq.m_Q0), m_Qe(dq.m_Qe)
    {
    }
    
    inline explicit basic_dualquat
    (const basic_quaternion<T>& q0, const basic_quaternion<T>& qe)
    :m_Q0(q0), m_Qe(qe)
    {
    }
    
    inline const basic_dualquat& operator=(const basic_dualquat& dq)
    {
      m_Q0 = dq.m_Q0, m_Qe = dq.m_Qe;
      return *this;
    }
    
    inline const basic_quaternion<T>& getQ0()const{ return m_Q0; }
    inline const basic_quaternion<T>& getQe()const{ return m_Qe; }
    
    /////
    
    const basic_dualquat operator-(void)const
    {
      return basic_dualquat(-m_Q0, -m_Qe);
    }
    
    const basic_dualquat operator+(const basic_dualquat& dq)const
    {
      return basic_dualquat(m_Q0 + dq.m_Q0, m_Qe + dq.m_Qe);
    }
    
    const basic_dualquat operator-(const basic_dualquat& dq)const
    {
      return basic_dualquat(m_Q0 - dq.m_Q0, m_Qe - dq.m_Qe);
    }
    
    const basic_dualquat operator*(T s)const
    {
      return basic_dualquat(m_Q0 * s, m_Qe * s);
    }
    
    const basic_dualquat operator*(const basic_dualquat& dq)const
    {
      return basic_dualquat(m_Q0 * dq.m_Q0, m_Q0 * dq.m_Qe + m_Qe * dq.m_Q0);
    }
    
    //////
    
    explicit basic_dualquat(const basic_quaternion<T>& rotation, 
                            const basic_vector3<T>& displacement)
    :m_Q0(rotation)
    {
      basic_quaternion<T> d(const_<T>::half() * displacement, const_<T>::zero());
      m_Qe = d * rotation;
    }
    
    const basic_vector3<T> getDisplacement()const
    {
      return const_<T>::two() * (m_Qe * conjugate(m_Q0)).getV();
    }
    
    const basic_quaternion<T> getRotation()const
    {
      return m_Q0;
    }
    
  private:
    basic_quaternion<T> m_Q0;
    basic_quaternion<T> m_Qe;
  };
  
  //////
  
  template<typename T>
  const basic_dualquat<T> normalize(const basic_dualquat<T>& dq)
  {
    const T l2 = lengthSqr(dq.getQ0());
    return dq * rsqrt(l2);
  }
  
  template<typename T>
  inline const basic_dualquat<T> select
  (const basic_dualquat<T>& dq0, const basic_dualquat<T>& dq1, 
   const bool_<T>& sel)
  {
    const basic_quaternion<T> q0 = select(dq0.getQ0(), dq1.getQ0(), sel);
    const basic_quaternion<T> qe = select(dq0.getQe(), dq1.getQe(), sel);
    return basic_dualquat<T>(q0, qe);
  }
  
}
