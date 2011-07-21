namespace cog{
  
  template<typename T>
  class bool_{
  };
  
  template<>
  class bool_<float>{
  public:
    typedef float T;
    
  public:
    inline bool_()
    {
    }
    
    inline bool_(const bool_& b): m_Value(b.m_Value)
    {
    }
    
    inline const bool_& operator=(const bool_& b)
    {
      m_Value = b.m_Value;
      return *this;
    }
    
    //////////
    
    inline const bool_ operator!()const
    {
      return bool_(!m_Value);
    }
    
    inline const bool_ operator&&(const bool_& b)const
    {
      return bool_(m_Value && b.m_Value);
    }
    
    inline const bool_ operator||(const bool_& b)const
    {
      return bool_(m_Value || b.m_Value);
    }
    
    /////////
    
    inline T select(T valNO, T valYES)const
    {
      if(m_Value)
        return valYES;
      return valNO;
    }
    
    static const bool_ less(T x, T y)
    {
      return bool_(x < y);
    }
    
    static const bool_ less_eq(T x, T y)
    {
      return bool_(x <= y);
    }
    
    static const bool_ equal(T x, T y)
    {
      return bool_(x == y);
    }
    
    /////////
    
    static const bool_ yes()
    {
      return bool_(true);
    }
    
    static const bool_ no()
    {
      return bool_(false);
    }
    
  public:
    bool _getRawValue()const{ return m_Value; }
    
  private:
    explicit bool_(bool rawval): m_Value(rawval)
    {
    }
    
  private:
    bool m_Value;
  };
  
}

