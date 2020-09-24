#include "engine.h"
#include <memory>

int main( int argc, char* argv[] )
{
  std::unique_ptr<Engine> engine = std::make_unique<Engine>();

  int height = 1000;
  int width = 1000;

  engine -> initialize( height, width );

  engine -> quit();
}
