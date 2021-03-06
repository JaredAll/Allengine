#ifndef PHYSICS_BALL
#define PHYSICS_BALL

#include "game_component.h"
#include "input_event.h"
#include "physics_component.h"
#include "sprite.h"
#include "test_component.h"
#include "sprite.h"
#include "test_component.h"

class PhysicsBall : public TestComponent
{
public:

  PhysicsBall( std::unique_ptr<WorldCoordinates> location_param,
               std::unique_ptr<PhysicsComponent> physics_component_param,
               std::unique_ptr<Sprite> ball_sprite_param );

  PhysicsBall( std::unique_ptr<WorldCoordinates> location_param,
               std::unique_ptr<Sprite> ball_sprite_param );

  bool accepting_input() override;

  std::vector<std::unique_ptr<Sprite>>& get_render_components() override;

  int get_width() override;

  int get_height() override;

  void update() override;

  void update( InputEvent& event ) override;

  void set_physics_component( std::unique_ptr<PhysicsComponent> physics_component );

  PhysicsComponent& get_physics_component();

  WorldCoordinates& get_location() const override;

  void set_location( std::unique_ptr<WorldCoordinates> new_location ) override;

  void accept_renderer( GameRenderer& renderer ) override;

  void mark_controllable();

private:

  bool controllable;
  std::vector<std::unique_ptr<Sprite>> render_components;
  std::unique_ptr<PhysicsComponent> physics_component;

};

#endif
