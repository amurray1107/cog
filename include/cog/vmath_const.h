namespace cog{
  
  namespace
  {
    template<>
    struct Const<float>{
      static const float ZERO;
      static const float ONE;
      static const float TWO;
      static const float NEONE;
      static const float RETWO;
    };
    
    const float Const<float>::ZERO = 0.0f;
    const float Const<float>::ONE = 1.0f;
    const float Const<float>::TWO = 2.0f;
    const float Const<float>::NEONE = -1.0f;
    const float Const<float>::RETWO = 0.5f;
  }
  
}

