#ifndef JAREDALL_WORLD_COORDINATES
#define JAREDALL_WORLD_COORDINATES

#include "point.h"
#include <memory>

class WorldCoordinates
{
public:

  WorldCoordinates( int x, int y );

  Point& get_location();
  
private:

  std::unique_ptr<Point> location;
  
};

#endif
