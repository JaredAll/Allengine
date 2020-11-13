#ifndef TEST_COMPONENT_FACTORY
#define TEST_COMPONENT_FACTORY

#include "game_renderer.h"
#include "physics_ball.h"

struct PhysicsBallInput
{
  int height;
  int width;
  std::string texture_path;
  int x;
  int y;
  float mass;
  bool inertial;
};

class TestComponentFactory
{
public:

  TestComponentFactory( GameRenderer& renderer );

  std::unique_ptr<PhysicsBall> build_physics_ball( PhysicsBallInput input );

private:

  GameRenderer& renderer;
};

#endif
