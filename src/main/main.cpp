#include "engine.h"
#include <cmath>
#include <memory>
#include "vector2.h"

int main( int argc, char* argv[] )
{
  std::unique_ptr<Engine> engine = std::make_unique<Engine>();

  int height = 1000;
  int width = 1000;

  std::unique_ptr<Vector2> first_vector2 = std::make_unique<Vector2>( 100, M_PI / 3 );

  std::cout << first_vector2 -> get_x_component() << std::endl;

  return 0;
}
