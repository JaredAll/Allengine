#include "test_component_factory.h"

using std::unique_ptr;
using std::make_unique;

TestComponentFactory::TestComponentFactory( GameRenderer& param_renderer )
  : renderer( param_renderer )
{
}

unique_ptr<PhysicsBall> TestComponentFactory::build_physics_ball( PhysicsBallInput input )
{
  unique_ptr<Sprite> sprite = make_unique<Sprite>(
      make_unique<WorldCoordinates>( 0, 0 ),
      input.height,
      input.width,
      renderer.create_texture( input.texture_path )
      );

    unique_ptr<PhysicsComponent> physics_component =
      make_unique<PhysicsComponent>( input.mass, input.inertial );

    unique_ptr<PhysicsBall> physics_ball = make_unique<PhysicsBall>(
      make_unique<WorldCoordinates>( input.x, input.y ),
      move( physics_component ),
      move( sprite )
      );

    return move( physics_ball );
}
