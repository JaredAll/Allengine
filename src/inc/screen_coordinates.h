#ifndef JAREDALL_SCREEN_COORDINATES
#define JAREDALL_SCREEN_COORDINATES

#include "point.h"
#include <memory>

class ScreenCoordinates
{
public:

  ScreenCoordinates( int x, int y, bool visible );

  Point& get_location();

  bool is_visible() const;
  
private:

  std::unique_ptr<Point> location;
  bool visible;
  
};

#endif
