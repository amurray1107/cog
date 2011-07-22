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
  
  
  
  
}

