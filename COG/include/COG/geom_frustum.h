namespace cog{
  
  ///////////////////
  // Frustum
  // : 
  // TEST: point v is inside the frustum IF planeN(v)>0,
  //        where, planeN(v) = dot(normalN, v) + distanceN
  //
  template<typename T>
  class basic_frustum{
  public:
    
    inline basic_frustum()
    {
    }
    
    inline basic_frustum(const basic_frustum& f):
    m_Left(f.m_Left), m_Right(f.m_Right), 
    m_Bottom(f.m_Bottom), m_Top(f.m_Top), 
    m_Near(f.m_Near), m_Far(f.m_Far)
    {
    }
    
    inline const basic_frustum& operator=(const basic_frustum& f)
    {
      m_Left = f.m_Left, m_Right = f.m_Right; 
      m_Bottom = f.m_Bottom, m_Top = f.m_Top;
      m_Near = f.m_Near, m_Far = f.m_Far;
      return *this;
    }
    
    explicit inline basic_frustum(const basic_matrix4<T>& m);
    
    inline const basic_plane<T>& getLeft()const{ return m_Left; }
    inline const basic_plane<T>& getRight()const{ return m_Right; }
    inline const basic_plane<T>& getBottom()const{ return m_Bottom; }
    inline const basic_plane<T>& getTop()const{ return m_Top; }
    inline const basic_plane<T>& getNear()const{ return m_Near; }
    inline const basic_plane<T>& getFar()const{ return m_Far; }
    
    //////////
    
    inline const bool_<T> test_visible(const basic_vector3<T>& v)const;
    inline const bool_<T> test_visible(const basic_sphere<T>& s)const;
    inline const bool_<T> test_visible(const basic_aabbox<T>& aabb)const;
    
  private:
    basic_plane<T>    m_Left;
    basic_plane<T>    m_Right;
    basic_plane<T>    m_Bottom;
    basic_plane<T>    m_Top;
    basic_plane<T>    m_Near;
    basic_plane<T>    m_Far;
    
  };
  
  template<typename T>
  inline basic_frustum<T>::basic_frustum(const basic_matrix4<T>& m)
  {
    const basic_matrix4<T> mt = transpose(m);

    const basic_vector4<T> l = mt.getColumn3() + mt.getColumn0();
    const basic_vector4<T> r = mt.getColumn3() - mt.getColumn0();
    const basic_vector4<T> b = mt.getColumn3() + mt.getColumn1();
    const basic_vector4<T> t = mt.getColumn3() - mt.getColumn1();
    const basic_vector4<T> n = mt.getColumn3() + mt.getColumn2();
    const basic_vector4<T> f = mt.getColumn3() - mt.getColumn2();
    
    m_Left = basic_plane<T>(l);
    m_Right = basic_plane<T>(r);
    m_Bottom = basic_plane<T>(b);
    m_Top = basic_plane<T>(t);
    m_Near = basic_plane<T>(n);
    m_Far = basic_plane<T>(f);

    if(true){
      m_Left = normalize(m_Left);
      m_Right = normalize(m_Right);
      m_Bottom = normalize(m_Bottom);
      m_Top = normalize(m_Top);
      m_Near = normalize(m_Near);
      m_Far = normalize(m_Far);
    }

  }
  
  template<typename T>
  inline const bool_<T> basic_frustum<T>::test_visible
  (const basic_vector3<T>& v)const
  {
    const T z = const_<T>::zero();
    
    bool_<T> b0 = bool_<T>::less_eq(z, getLeft().func(v));
    b0 = b0 && bool_<T>::less_eq(z, getRight().func(v));
    b0 = b0 && bool_<T>::less_eq(z, getBottom().func(v));
    b0 = b0 && bool_<T>::less_eq(z, getTop().func(v));
    b0 = b0 && bool_<T>::less_eq(z, getNear().func(v));
    b0 = b0 && bool_<T>::less_eq(z, getFar().func(v));
    
    return b0;
  }
  
  template<typename T>
  inline const bool_<T> basic_frustum<T>::test_visible
  (const basic_sphere<T>& s)const
  {
    const T pr = s.getRadius();
    const T nr = negate(pr);

    bool_<T> b0 = bool_<T>::less_eq(nr, getLeft().func(s.getCenter()));
    b0 = b0 && bool_<T>::less_eq(nr,getRight().func(s.getCenter()));
    b0 = b0 && bool_<T>::less_eq(nr, getBottom().func(s.getCenter()));
    b0 = b0 && bool_<T>::less_eq(nr, getTop().func(s.getCenter()));
    b0 = b0 && bool_<T>::less_eq(nr, getNear().func(s.getCenter()));
    b0 = b0 && bool_<T>::less_eq(nr, getFar().func(s.getCenter()));
    
    return b0;
  }

  template<typename T>
  inline const bool_<T> basic_frustum<T>::test_visible
  (const basic_aabbox<T>& aabb)const
  {
    bool_<T> b0 = backface(getLeft(), aabb);
    b0 = b0 || backface(getRight(), aabb);
    b0 = b0 || backface(getBottom(), aabb);
    b0 = b0 || backface(getTop(), aabb);
    b0 = b0 || backface(getNear(), aabb);
    b0 = b0 || backface(getFar(), aabb);

    return !b0;
  }
  
}

