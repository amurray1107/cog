//
#include "../CRoot.h"

//
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//
namespace Leo{

  class CRootWIN : public CRoot{
  public: // Constructor & Destructor
    CRootWIN();
    virtual ~CRootWIN();

  public: // Inherited From Super
    virtual void run();

  public: // Extended Methods
    void _preInitialize(::HINSTANCE hInst);
    int _getMessageLoopResult()const;

  private: // Private Fields
    ::HINSTANCE m_Instance;
    int m_ExecutionResult;
    int m_NumWindowsCreated;

  };

}

