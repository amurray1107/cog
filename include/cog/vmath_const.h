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
  
  template<typename T>
  struct ConstVector3{
    
    static const basic_vector3<T> xAxis()
    {
      return basic_vector3<T>(Const<T>::ONE, Const<T>::ZERO, Const<T>::ZERO);
    }
    
    static const basic_vector3<T> yAxis()
    {
      return basic_vector3<T>(Const<T>::ZERO, Const<T>::ONE, Const<T>::ZERO);
    }
    
    static const basic_vector3<T> zAxis()
    {
      return basic_vector3<T>(Const<T>::ZERO, Const<T>::ZERO, Const<T>::ONE);
    }
    
  };
  
  template<typename T>
  struct ConstVector4{
    
    static const basic_vector4<T> xAxis()
    {
      return basic_vector4<T>(Const<T>::ONE, Const<T>::ZERO, 
                              Const<T>::ZERO, Const<T>::ZERO);
    }
    
    static const basic_vector4<T> yAxis()
    {
      return basic_vector4<T>(Const<T>::ZERO, Const<T>::ONE, 
                              Const<T>::ZERO, Const<T>::ZERO);
    }
    
    static const basic_vector4<T> zAxis()
    {
      return basic_vector4<T>(Const<T>::ZERO, Const<T>::ZERO, 
                              Const<T>::ONE, Const<T>::ZERO);
    }
    
    static const basic_vector4<T> wAxis()
    {
      return basic_vector4<T>(Const<T>::ZERO, Const<T>::ZERO, 
                              Const<T>::ZERO, Const<T>::ONE);
    }
    
  };
  
  template<typename T>
  struct ConstMatrix3{
    
    static const basic_matrix3<T> identity()
    {
      const basic_vector3<T> xa = ConstVector3<T>::xAxis();
      const basic_vector3<T> ya = ConstVector3<T>::yAxis();
      const basic_vector3<T> za = ConstVector3<T>::zAxis();
      return basic_matrix3<T>(xa, ya, za);
    }
    
  };
  
  template<typename T>
  struct ConstMatrix4{
    
    static const basic_matrix4<T> identity()
    {
      const basic_vector4<T> xa = ConstVector4<T>::xAxis();
      const basic_vector4<T> ya = ConstVector4<T>::yAxis();
      const basic_vector4<T> za = ConstVector4<T>::zAxis();
      const basic_vector4<T> wa = ConstVector4<T>::wAxis();
      return basic_matrix4<T>(xa, ya, za, wa);
    }
    
  };
  
}

