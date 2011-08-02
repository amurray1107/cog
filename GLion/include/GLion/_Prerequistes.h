#pragma once

#include <COG/cog.h>

// C++
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <deque>

namespace GLion{
  
  //
  using std::string;
  using std::vector;
  using std::list;
  using std::map;
  using std::set;
  using std::stack;
  using std::queue;
  using std::deque;
  
  //
  class CStringParam{
  public:
    CStringParam(const char* cstr):m_CStr(cstr){}
    CStringParam(const string& s):m_CStr(s.c_str()){}
    
    const char* get()const{ return m_CStr; }
    
  private:
    const char* m_CStr;
    
  };
  
}
