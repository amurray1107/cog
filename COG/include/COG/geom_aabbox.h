namespace cog{
  
  ///////////////////////////////
  // AABBox (Axis-Aligned Bounding Box)
  // : 
  //
  template<typename T>
  class basic_aabbox{
  public:
    
    inline basic_aabbox()
    {
    }
    
    inline basic_aabbox(const basic_aabbox& b):
    m_MinVec(b.m_MinVec), m_MaxVec(b.m_MaxVec)
    {
    }
    
    inline const basic_aabbox& operator=(const basic_aabbox& b)
    {
      m_MinVec = b.m_MinVec, m_MaxVec = b.m_MaxVec;
      return *this;
    }
    
    /////////
    
    inline const basic_vector3<T>& getMinVec()const{ return m_MinVec; }
    inline const basic_vector3<T>& getMaxVec()const{ return m_MaxVec; }
    
    /////////
    
    inline explicit basic_aabbox
    (const basic_vector3<T>& minvec, const basic_vector3<T>& maxvec):
    m_MinVec(minvec), m_MaxVec(maxvec)
    {
    }
    
    inline explicit basic_aabbox(T s):
    m_MinVec(s), m_MaxVec(s)
    {
    }
    
    /////////
    
    inline void join(const basic_vector3<T>& vec)
    {
      m_MinVec = min(m_MinVec, vec);
      m_MaxVec = max(m_MaxVec, vec);
    }
    
  private:
    basic_vector3<T>  m_MinVec;
    basic_vector3<T>  m_MaxVec;
    
  };
  
  ///////////////
  
  template<typename T>
  inline const bool_<T> intersect
  (const basic_aabbox<T>& a, const basic_aabbox<T>& b)
  {
    const basic_vector3<T> ami = a.getMinVec();
    const basic_vector3<T> amx = a.getMaxVec();
    const basic_vector3<T> bmi = b.getMinVec();
    const basic_vector3<T> bmx = b.getMaxVec();

    bool_<T> x0 = bool_<T>::less(bmx.getX(), ami.getX());
    x0 = x0 || bool_<T>::less(amx.getX(), bmi.getX());
    x0 = x0 || bool_<T>::less(bmx.getY(), ami.getY());
    x0 = x0 || bool_<T>::less(amx.getY(), bmi.getY());
    x0 = x0 || bool_<T>::less(bmx.getZ(), ami.getZ());
    x0 = x0 || bool_<T>::less(amx.getZ(), bmi.getZ());

    return !x0;
  }

  template<typename T>
  inline const bool_<T> intersect
  (const basic_aabbox<T>& aabb, const basic_sphere<T>& s)
  {
    basic_vector3<T> e;
    e = max(aabb.getMinVec() - s.getCenter(), const_vector3<T>::zero());
    e = e + max(s.getCenter() - aabb.getMaxVec(), const_vector3<T>::zero());

    const T d = dot(e, e);

    return bool_<T>::less_eq(d, mul(s.getRadius(), s.getRadius()));
  }

  template<typename T>
  inline void _intersect
  ( const basic_aabbox<T>& aabb, const basic_plane<T>& p,
   bool_<T>& front, bool_<T>& back, bool_<T>& intersection)
  {
    basic_vector3<T> c, h;
    c = const_<T>::half() * (aabb.getMaxVec() + aabb.getMinVec());
    h = const_<T>::half() * (aabb.getMaxVec() - aabb.getMinVec());
    
    const T e = dot(h, abs(p.getNormal()));
    const T s = p.func(c);

    front = bool_<T>::less(const_<T>::zero(), sub(s, e));
    back = bool_<T>::less(add(s, e), const_<T>::zero());
    intersection = !(front||back);
  }
  
  template<typename T>
  inline const bool_<T> intersect
  (const basic_plane<T>& p, const basic_aabbox<T>& aabb)
  {
    bool_<T> front, back, intersection;
    _intersect(aabb, p, front, back, intersection);
    return intersection;
  }

  template<typename T>
  inline const bool_<T> frontface
  (const basic_plane<T>& p, const basic_aabbox<T>& aabb)
  {
    bool_<T> front, back, intersection;
    _intersect(aabb, p, front, back, intersection);
    return front;
  }

  template<typename T>
  inline const bool_<T> backface
  (const basic_plane<T>& p, const basic_aabbox<T>& aabb)
  {
    bool_<T> front, back, intersection;
    _intersect(aabb, p, front, back, intersection);
    return back;
  }

}

