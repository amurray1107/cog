#pragma once

//
#include "_Prerequisites.h"

//
namespace Leo{
  
  class IViewport{
  public:
    
    //
    virtual F32 getOriginX()const=0;
    virtual F32 getOriginY()const=0;
    
    //
    virtual F32 getWidth()const=0;
    virtual F32 getHeight()const=0;
    
  };
  
  //
  // Viewport Coordinate Frame
  //
  //  ^ (+Y)
  //  |
  //  |    <---- WIDTH ---->
  //  |   + --------------- + 
  //  |   |                 | ^
  //  |   |                 | | HEIGHT
  //  |   |                 | |
  //  |   |                 | v
  //  |   x --------------- +
  //  |  (Origin)
  //  |
  //  L-------------------------> (+X)
  //  (0, 0)
  //
  
  // Viewport that Fills Render Target
  //    Origin = (0.0, 0.0)
  //    Size = (1.0, 1.0)
  
}

