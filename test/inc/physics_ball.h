#ifndef PHYSICS_BALL
#define PHYSICS_BALL

#include "test_component.h"
#include "sprite.h"

class PhysicsBall : public TestComponent
{
public:

  PhysicsBall( std::unique_ptr<WorldCoordinates> location_param,
               std::unique_ptr<Sprite> ball_sprite_param );

  bool accepting_input() override;

  std::vector<std::unique_ptr<Sprite>>& get_render_components() override;

  int get_width() override;

  int get_height() override;

private:

  std::vector<std::unique_ptr<Sprite>> render_components;

};

#endif
