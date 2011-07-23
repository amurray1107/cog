namespace cog{
  
  template<typename T>
  struct const_{
    //
  };
  
  template<>
  struct const_<F32>{
    static F32 zero(){ return 0.0f; }
    static F32 one(){ return 1.0f; }
    static F32 two(){ return 2.0f; }
    static F32 neOne(){ return -1.0f; }
    static F32 half(){ return 0.5f; }
    static F32 _slerp_tol(){ return 1.0f - 0.0000001f; }
  };
  
}

