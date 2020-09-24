#ifndef JAREDALL_ALLENGINE_VECTOR2
#define JAREDALL_ALLENGINE_VECTOR2

class Vector2
{
public:

  Vector2( float param_magnitude, float param_theta );

  float get_x_component();

  float get_y_component();

private:

  float magnitude;
  float theta;

};


#endif
