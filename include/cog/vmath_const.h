namespace cog{
  
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
  
  template<typename T>
  struct const_vector3{
    
    static const basic_vector3<T> xAxis()
    {
      return basic_vector3<T>(const_<T>::ONE, const_<T>::ZERO, 
                              const_<T>::ZERO);
    }
    
    static const basic_vector3<T> yAxis()
    {
      return basic_vector3<T>(const_<T>::ZERO, const_<T>::ONE, 
                              const_<T>::ZERO);
    }
    
    static const basic_vector3<T> zAxis()
    {
      return basic_vector3<T>(const_<T>::ZERO, const_<T>::ZERO, 
                              const_<T>::ONE);
    }
    
  };
  
  template<typename T>
  struct const_vector4{
    
    static const basic_vector4<T> xAxis()
    {
      return basic_vector4<T>(const_<T>::ONE, const_<T>::ZERO, 
                              const_<T>::ZERO, const_<T>::ZERO);
    }
    
    static const basic_vector4<T> yAxis()
    {
      return basic_vector4<T>(const_<T>::ZERO, const_<T>::ONE, 
                              const_<T>::ZERO, const_<T>::ZERO);
    }
    
    static const basic_vector4<T> zAxis()
    {
      return basic_vector4<T>(const_<T>::ZERO, const_<T>::ZERO, 
                              const_<T>::ONE, const_<T>::ZERO);
    }
    
    static const basic_vector4<T> wAxis()
    {
      return basic_vector4<T>(const_<T>::ZERO, const_<T>::ZERO, 
                              const_<T>::ZERO, const_<T>::ONE);
    }
    
  };
  
  template<typename T>
  struct const_matrix3{
    
    static const basic_matrix3<T> identity()
    {
      const basic_vector3<T> xa = const_vector3<T>::xAxis();
      const basic_vector3<T> ya = const_vector3<T>::yAxis();
      const basic_vector3<T> za = const_vector3<T>::zAxis();
      return basic_matrix3<T>(xa, ya, za);
    }
    
  };
  
  template<typename T>
  struct const_matrix4{
    
    static const basic_matrix4<T> identity()
    {
      const basic_vector4<T> xa = const_vector4<T>::xAxis();
      const basic_vector4<T> ya = const_vector4<T>::yAxis();
      const basic_vector4<T> za = const_vector4<T>::zAxis();
      const basic_vector4<T> wa = const_vector4<T>::wAxis();
      return basic_matrix4<T>(xa, ya, za, wa);
    }
    
  };
  
}

