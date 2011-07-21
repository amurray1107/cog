namespace cog{
  
  template<typename T>
  struct const_{
    //
  };
  
  template<>
  struct const_<float>{
    static float zero(){ return 0.0f; }
    static float one(){ return 1.0f; }
    static float two(){ return 2.0f; }
    static float neOne(){ return -1.0f; }
    static float half(){ return 0.5f; }
  };
  
}

