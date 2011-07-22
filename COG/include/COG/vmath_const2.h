namespace cog{
  
  template<typename T>
  struct const_vector3{
    
    static const basic_vector3<T> xAxis()
    {
      return basic_vector3<T>(const_<T>::one(), const_<T>::zero(), 
                              const_<T>::zero());
    }
    
    static const basic_vector3<T> yAxis()
    {
      return basic_vector3<T>(const_<T>::zero(), const_<T>::one(), 
                              const_<T>::zero());
    }
    
    static const basic_vector3<T> zAxis()
    {
      return basic_vector3<T>(const_<T>::zero(), const_<T>::zero(), 
                              const_<T>::one());
    }
    
    static const basic_vector3<T> zero()
    {
      return basic_vector3<T>(const_<T>::zero());
    }
    
  };
  
  template<typename T>
  struct const_vector4{
    
    static const basic_vector4<T> xAxis()
    {
      return basic_vector4<T>(const_<T>::one(), const_<T>::zero(), 
                              const_<T>::zero(), const_<T>::zero());
    }
    
    static const basic_vector4<T> yAxis()
    {
      return basic_vector4<T>(const_<T>::zero(), const_<T>::one(), 
                              const_<T>::zero(), const_<T>::zero());
    }
    
    static const basic_vector4<T> zAxis()
    {
      return basic_vector4<T>(const_<T>::zero(), const_<T>::zero(), 
                              const_<T>::one(), const_<T>::zero());
    }
    
    static const basic_vector4<T> wAxis()
    {
      return basic_vector4<T>(const_<T>::zero(), const_<T>::zero(), 
                              const_<T>::zero(), const_<T>::one());
    }
    
    static const basic_vector4<T> zero()
    {
      return basic_vector4<T>(const_<T>::zero());
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
    
    static const basic_matrix3<T> zero()
    {
      return basic_matrix3<T>(const_<T>::zero());
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
    
    static const basic_matrix4<T> zero()
    {
      return basic_matrix4<T>(const_<T>::zero());
    }
    
  };
  
  template<typename T>
  struct const_quaternion{
    
    static const basic_quaternion<T> identity()
    {
      const basic_vector3<T> zv(const_<T>::zero());
      return basic_quaternion<T>(zv, const_<T>::one());
    }
    
    static const basic_quaternion<T> zero()
    {
      const basic_vector3<T> zv(const_<T>::zero());
      return basic_quaternion<T>(zv, const_<T>::zero());
    }
    
  };
  
}

