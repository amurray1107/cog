#ifndef __X86_SSE__
#  error _bool_sse.h is included while SSE is not supported
#endif

#ifndef __X86_SSE2__
#  error _bool_sse.h is included while SSE2 is not supported
#endif

namespace cog{
  
  template<>
  class bool_<VF32>{
  public:
    typedef VF32 T;
    
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
    
    /////////
    
    inline const bool_ operator!()const
    {
      return bool_(_mm_xor_ps(m_Value, _i2f(_mm_set1_epi32(0xffffffff))));
    }
    
    inline const bool_ operator&&(const bool_& b)const
    {
      return bool_(_mm_and_ps(m_Value, b.m_Value));
    }
    
    inline const bool_ operator||(const bool_& b)const
    {
      return bool_(_mm_or_ps(m_Value, b.m_Value));
    }
    
    /////////
    
    inline T select(T valNO, T valYES)const
    {
      __m128 x = _mm_andnot_ps(m_Value, valNO);
      __m128 y = _mm_and_ps(m_Value, valYES);
      return _mm_or_ps(x, y);
    }
    
    static const bool_ less(T x, T y)
    {
      return bool_(_mm_cmplt_ps(x,y));
    }
    
    static const bool_ less_eq(T x, T y)
    {
      return bool_(_mm_cmple_ps(x,y));
    }
    
    static const bool_ equal(T x, T y)
    {
      return bool_(_mm_cmpeq_ps(x,y));
    }
    
    /////////
    
    static const bool_ yes()
    {
      return bool_(_i2f(_mm_set1_epi32(0xffffffff)));
    }
    
    static const bool_ no()
    {
      return bool_(_i2f(_mm_set1_epi32(0x0)));
    }
    
  public:
    bool _isSameAs(bool b)const
    {
      const I32 t = (b?0xffffffff:0x0);
      const I32* p = (I32*)&m_Value;
      return (p[0]==t && p[1]==t && p[2]==t && p[3]==t);
    }
    
  private:
    explicit bool_(__m128 rawval): m_Value(rawval)
    {
    }
    
  private:
    __m128 m_Value;
    
  };
  
}

