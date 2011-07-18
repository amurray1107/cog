namespace cog{
  
  namespace
  {
    template<typename T>
    struct const_{
      //
    };
  }
  
  namespace
  {
    template<>
    struct const_<float>{
      static const float ZERO;
      static const float ONE;
      static const float TWO;
      static const float NEONE;
      static const float RETWO;
    };
    
    const float const_<float>::ZERO = 0.0f;
    const float const_<float>::ONE = 1.0f;
    const float const_<float>::TWO = 2.0f;
    const float const_<float>::NEONE = -1.0f;
    const float const_<float>::RETWO = 0.5f;
  }
  
}

