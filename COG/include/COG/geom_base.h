#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace cog{
  
  ///////////////////////////////
  // Ray
  // : v0 + dir(t)
  //
  template<typename T>
  class basic_ray{
  public:
    
    inline basic_ray()
    {
    }
    
    inline basic_ray(const basic_ray& r):
    m_Origin(r.m_Origin), m_Direction(r.m_Direction)
    {
    }
    
    inline const basic_ray& operator=(const basic_ray& r)
    {
      m_Origin = r.m_Origin, m_Direction = r.m_Direction;
      return *this;
    }
    
    ///////////
    
    inline const basic_vector3<T>& getOrigin()const{ return m_Origin; }
    inline const basic_vector3<T>& getDirection()const{ return m_Direction; }
    
    ///////////
    
    inline explicit basic_ray
    (const basic_vector3<T>& orig, const basic_vector3<T>& dir):
    m_Origin(orig), m_Direction(dir)
    {
    }
    
    ///////////
    
  private:
    basic_vector3<T> m_Origin;
    basic_vector3<T> m_Direction;
    
  };
  
  ///////////////////////////////
  // Plane
  // : aX + bY + cZ + d = 0
  // # normal = (a, b, c)
  // # dist = d
  //
  template<typename T>
  class basic_plane{
  public:
    
    inline basic_plane()
    {
    }
    
    inline basic_plane(const basic_plane& p):
    m_Normal(p.m_Normal), m_Distance(p.m_Distance)
    {
    }
    
    inline const basic_plane& operator=(const basic_plane& p)
    {
      m_Normal = p.m_Normal, m_Distance = p.m_Distance;
      return *this;
    }
    
    //////////
    
    inline const basic_vector3<T>& getNormal()const{ return m_Normal; }
    inline T getDistance()const{ return m_Distance; }
    
    //////////
    
    inline explicit basic_plane(const basic_vector3<T>& normal, T dist):
    m_Normal(normal), m_Distance(dist)
    {
    }
    
    inline explicit basic_plane(const basic_vector4<T>& v):
    m_Normal(v.getX(), v.getY(), v.getZ()), m_Distance(v.getW())
    {
    }
    
    //////////
    
    inline T func(const basic_vector3<T>& v)const
    {
      return add(dot(m_Normal, v), m_Distance);
    }
    
    /////////
    
  private:
    basic_vector3<T>  m_Normal;
    T                 m_Distance;
    
  };
  
  ///////////////////////////////
  // Sphere
  // : length((X,Y,Z) - center)^2 - radius^2 = 0;
  //
  template<typename T>
  class basic_sphere{
  public:
    
    inline basic_sphere()
    {
    }
    
    inline basic_sphere(const basic_sphere& s):
    m_Center(s.m_Center), m_Radius(s.m_Radius)
    {
    }
    
    inline const basic_sphere& operator=(const basic_sphere& s)
    {
      m_Center = s.m_Center, m_Radius = s.m_Radius;
      return *this;
    }
    
    ////////////
    
    inline const basic_vector3<T>& getCenter()const{ return m_Center; }
    inline T getRadius()const{ return m_Radius; }
    
    ////////////
    
    inline explicit basic_sphere(const basic_vector3<T>& center, T radius):
    m_Center(center), m_Radius(radius)
    {
    }
    
    ////////////
    
    inline T func(const basic_vector3<T>& v)const
    {
      T r = m_Radius;
      return nmsub(r, r, lengthSqr(m_Center - v));
    }
    
  private:
    basic_vector3<T>  m_Center;
    T                 m_Radius;
    
  };
  
}

////////////////////////////////////////////////////////////////////////////////

namespace cog{
  
  template<typename T>
  inline const basic_plane<T> normalize(const basic_plane<T>& p)
  {
    T rl2 = rsqrt(lengthSqr(p.getNormal()));
    return basic_plane<T>(p.getNormal() * rl2, mul(rl2, p.getDistance()));
  }
  
  template<typename T>
  inline const basic_ray<T> normalize(const basic_ray<T>& r)
  {
    return basic_ray<T>(r.getOrigin(), normalize(r.getDirection()));
  }
  
}

namespace cog{
  
  template<typename T>
  inline const bool_<T> intersect
  (const basic_sphere<T>& s0, const basic_sphere<T>& s1)
  {
    const T d2 = lengthSqr(s1.getCenter()-s0.getCenter());
    const T rs = add(s1.getRadius(), s0.getRadius());
    const T rs2 = mul(rs, rs);

    return bool_<T>::less_eq(d2, rs2);
  }
  
}

////////////////////////////////////////////////////////////////////////////////

