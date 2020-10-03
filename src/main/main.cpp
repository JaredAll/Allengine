#include "engine.h"
#include <cmath>
#include <memory>
#include "vector2.h"

int main( int argc, char* argv[] )
{
  std::unique_ptr<Engine> engine = std::make_unique<Engine>();

  int height = 1000;
  int width = 1000;

  std::unique_ptr<Vector2<Force>> first_vector2 = std::make_unique<Vector2<Force>>( 100, M_PI / 4 );
  std::unique_ptr<Vector2<Force>> second_vector2 = std::make_unique<Vector2<Force>>( 50, M_PI / 4 );

  std::unique_ptr<Vector2<Force>> third = *first_vector2 + ( *second_vector2 );

  std::cout << third -> get_x_component() << std::endl;
  std::cout << third -> get_y_component() << std::endl;

  return 0;
}
