#ifndef JAREDALL_ALLENGINE_VECTOR2
#define JAREDALL_ALLENGINE_VECTOR2

#include <memory>

class Vector2
{
public:

  Vector2( float param_magnitude, float param_theta );

  float get_x_component() const;

  float get_y_component() const;

  float get_magnitude() const;

  float get_theta() const;

  std::unique_ptr<Vector2> add( Vector2 const& vector );

private:

  float magnitude;
  float theta;

};


#endif