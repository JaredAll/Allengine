#ifndef JAREDALL_SCREEN_COORDINATES
#define JAREDALL_SCREEN_COORDINATES

#include "point.h"
#include <memory>

class ScreenCoordinates
{
public:

  ScreenCoordinates( int x, int y, bool visible );

  int get_screen_x() const;

  int get_screen_y () const;

  bool is_visible() const;

  friend std::ostream& operator<<( std::ostream& os, const ScreenCoordinates& coordinates );
  
private:

  int x;
  int y;
  bool visible;
  
};

#endif
