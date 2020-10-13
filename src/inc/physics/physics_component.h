#ifndef JAREDALL_ALLENGINE_PHYSICS_COMPONENT
#define JAREDALL_ALLENGINE_PHYSICS_COMPONENT

#include <memory>
#include "vector_qualities.h"
#include "vector2.h"
#include <vector>

class PhysicsComponent
{
public:
  
  PhysicsComponent( float mass, bool inertial );

  void consider( std::unique_ptr<Vector2<Force>> force );

  void remove( std::unique_ptr<Vector2<Force>> force );

  std::unique_ptr<Vector2<Displacement>> advance( float delta_t );

  bool is_inertial();

  void freeze();

private:

  std::unique_ptr<Vector2<Displacement>> location;
  std::unique_ptr<Vector2<Velocity>> velocity;
  std::unique_ptr<Vector2<Acceleration>> acceleration;
  std::vector<std::unique_ptr<Vector2<Force>>> forces;

  float mass;
  bool inertial;

};

#endif
