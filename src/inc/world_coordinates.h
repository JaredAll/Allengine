#ifndef JAREDALL_WORLD_COORDINATES
#define JAREDALL_WORLD_COORDINATES

#include "point.h"
#include <memory>

class WorldCoordinates
{
public:

  WorldCoordinates( int x, int y );

  int get_world_x() const;

  void set_world_x( int x );

  int get_world_y() const;

  void set_world_y( int y );

  std::unique_ptr<WorldCoordinates> operator+( WorldCoordinates const& other ) const;

  friend std::ostream& operator<<( std::ostream& os, const WorldCoordinates& coordinates );

private:

  int x;
  int y;
  
};

#endif
