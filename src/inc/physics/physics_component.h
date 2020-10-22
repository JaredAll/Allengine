#ifndef JAREDALL_ALLENGINE_PHYSICS_COMPONENT
#define JAREDALL_ALLENGINE_PHYSICS_COMPONENT

#include <memory>
#include "vector_qualities.h"
#include "vector2.h"
#include "world_coordinates.h"
#include <vector>
#include "world_coordinates.h"

class PhysicsComponent
{
public:
  
  PhysicsComponent( float mass, bool inertial );

  void consider( std::unique_ptr<Vector2<Force>> force );

  void remove( std::unique_ptr<Vector2<Force>> force );

  std::unique_ptr<Vector2<Displacement>> advance( float delta_t );

  bool is_inertial();

  void freeze();

  WorldCoordinates& get_location();

  void set_location( std::unique_ptr<WorldCoordinates> coordinates );

  void set_velocity( std::unique_ptr<Vector2<Velocity>> velocity );

  Vector2<Velocity>& get_velocity();

private:

  std::unique_ptr<WorldCoordinates> location;
  std::unique_ptr<Vector2<Displacement>> displacement;
  std::unique_ptr<Vector2<Velocity>> velocity;
  std::unique_ptr<Vector2<Acceleration>> acceleration;
  std::vector<std::unique_ptr<Vector2<Force>>> forces;

  float mass;
  bool inertial;

};

#endif
