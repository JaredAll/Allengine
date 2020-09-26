#ifndef JAREDALL_SCREEN_WINDOW
#define JAREDALL_SCREEN_WINDOW

#include "world_coordinates.h"
#include "screen_coordinates.h"
#include <memory>

class ScreenWindow
{
public:

  ScreenWindow( std::unique_ptr<WorldCoordinates> upper_left_corner,
                std::unique_ptr<WorldCoordinates> lower_right_corner );

  std::unique_ptr<ScreenCoordinates> project( WorldCoordinates& coordinates );

private:

  std::unique_ptr<WorldCoordinates> upper_left_corner;
  std::unique_ptr<WorldCoordinates> lower_right_corner;
  
};

#endif
