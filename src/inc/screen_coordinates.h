#ifndef JAREDALL_SCREEN_COORDINATES
#define JAREDALL_SCREEN_COORDINATES

#include "point.h"
#include <memory>

class ScreenCoordinates
{
public:

  ScreenCoordinates( int x, int y );

  Point& get_location();
  
private:

  std::unique_ptr<Point> location;
  
};

#endif
