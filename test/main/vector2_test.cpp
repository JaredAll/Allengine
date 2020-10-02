#include "catch.hpp"
#include "vector2.h"
#include <cmath>
#include <iostream>
#include "vector_qualities.h"

#define EPSILON 0.0001

using std::unique_ptr;
using std::make_unique;

bool withinEpsilon( float value_one, float value_two )
{
  return std::abs( value_one - value_two ) < EPSILON;
}

TEST_CASE( "add vectors with equivalent angles" )
{
  SECTION( "pi / 4 radians" )
  {
    float theta = M_PI / 4;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, theta );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 50, theta );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );

    float result_theta = result -> get_theta(); 

    REQUIRE( withinEpsilon( result_theta, theta ) );
    REQUIRE( result -> get_magnitude() == 150 );
  }

  SECTION( "3 pi / 4 radians" )
  {
    float theta = 3 * M_PI / 4;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, theta );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 50, theta );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );

    float result_theta = result -> get_theta(); 

    REQUIRE( withinEpsilon( result_theta, theta ) );
    REQUIRE( result -> get_magnitude() == 150 );
  }

  SECTION( "5 pi / 4 radians" )
  {
    float theta = 5 * M_PI / 4;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, theta );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 50, theta );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );

    float result_theta = result -> get_theta(); 

    REQUIRE( withinEpsilon( result_theta, theta ) );
    REQUIRE( result -> get_magnitude() == 150 );
  }

  SECTION( "7 pi / 4 radians" )
  {
    float theta = 7 * M_PI / 4;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, theta );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 50, theta );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta(); 

    REQUIRE( withinEpsilon( result_theta, theta ) );
    REQUIRE( result -> get_magnitude() == 150 );
  }

  SECTION( "pi radians" )
  {
    float theta = M_PI;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, theta );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 50, theta );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );

    float result_theta = result -> get_theta(); 

    REQUIRE( withinEpsilon( result_theta, theta ) );
    REQUIRE( result -> get_magnitude() == 150 );
  }
}

TEST_CASE( "add vectors with supplementary angles" )
{
  SECTION( "pi / 2 with greater magnitude and 3 pi / 2 radians" )
  {
    float pi_over_two = M_PI / 2;
    float three_pi_over_two = 3 * M_PI / 2;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, pi_over_two );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 50, three_pi_over_two );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );

    float result_theta = result -> get_theta();
    float result_x_component = result -> get_x_component();
    float result_y_component = result -> get_y_component();

    REQUIRE( withinEpsilon( result_x_component, 0 ) );
    REQUIRE( withinEpsilon( result_y_component, 50 ) );
    REQUIRE( withinEpsilon( pi_over_two, result_theta ) );
    REQUIRE( result -> get_magnitude() == 50 );
  }

  SECTION( "3 pi / 2 with greater magnitude and pi / 2 radians" )
  {
    float pi_over_two = M_PI / 2;
    float three_pi_over_two = 3 * M_PI / 2;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 50, pi_over_two );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 100, three_pi_over_two );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();
    float result_x_component = result -> get_x_component();
    float result_y_component = result -> get_y_component();

    REQUIRE( withinEpsilon( result_x_component, 0 ) );
    REQUIRE( withinEpsilon( result_y_component, -1 * 50 ) );
    REQUIRE( withinEpsilon( three_pi_over_two, result_theta ) );
    REQUIRE( result -> get_magnitude() == 50 );
  }

  SECTION( "pi / 4 with greater magnitude and 5 pi / 4 radians" )
  {
    float pi_over_four = M_PI / 4;
    float five_pi_over_four = 5 * M_PI / 4;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, pi_over_four );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 50, five_pi_over_four );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( pi_over_four, result_theta ) );
    REQUIRE( result -> get_magnitude() == 50 );
  }

  SECTION( "5 pi / 4 with greater magnitude and pi / 4 radians" )
  {
    float pi_over_four = M_PI / 4;
    float five_pi_over_four = 5 * M_PI / 4;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 50, pi_over_four );
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 100, five_pi_over_four );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( five_pi_over_four, result_theta ) );
    REQUIRE( result -> get_magnitude() == 50 );
  }
}

TEST_CASE( "first quadrant vector" )
{
  float pi_over_three = M_PI / 3;
  unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 9, pi_over_three );

  SECTION( "plus a first quadrant vector" )
  {
    float pi_over_six = M_PI / 6;
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 11, pi_over_six );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 19.3254 ) );
    REQUIRE( result -> get_theta() - 0.7586 < EPSILON );
  }

  SECTION( "plus a second quadrant vector" )
  {
    float five_pi_over_six = 5 * M_PI / 6;
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 11, five_pi_over_six );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 14.2126 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 1.9322 ) );
  }

  SECTION( "plus a third quadrant vector" )
  {
    float seven_pi_over_six = 7 * M_PI / 6;
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 11, seven_pi_over_six );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 5.5251 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 2.71339 ) );
  }

  SECTION( "plus a fourth quadrant vector" )
  {
    float eleven_pi_over_six = 11 * M_PI / 6;
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 11, eleven_pi_over_six );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 14.2126 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 0.16213 ) );
  }
}

TEST_CASE( "a second quadrant vector" )
{
  float three_pi_over_four = 3 * M_PI / 4;
  unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 5, three_pi_over_four );

  SECTION( "plus a second quadrant vector" )
  {
    float two_pi_over_three = 2 * M_PI / 3;

    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 7, two_pi_over_three );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 11.9002 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 2.2033 ) );
  }

  SECTION( "plus a third quadrant vector" )
  {
    float four_pi_over_three = 4 * M_PI / 3;

    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 7, four_pi_over_three );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 7.4754 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 3.4863 ) );
  }

  SECTION( "plus a fourth quadrant vector" )
  {
    float five_pi_over_three = 5 * M_PI / 3;

    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 7, five_pi_over_three );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 2.52688 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 4.6983 ) );
  }
}

TEST_CASE( "a third quadrant vector" )
{
  float seven_pi_over_six = 7 * M_PI / 6;
  unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 100, seven_pi_over_six );

  SECTION( "plus a third quadrant vector" )
  {
    float five_pi_over_four = 5 * M_PI / 4;

    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 200, five_pi_over_four );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 297.7197 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 3.8399 ) );
  }

  SECTION( "plus a fourth quadrant vector" )
  {
    float seven_pi_over_four = 7 * M_PI / 4;

    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 200, seven_pi_over_four );

    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );
    
    float result_theta = result -> get_theta();

    REQUIRE( withinEpsilon( result -> get_magnitude(), 199.1161 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 4.9913 ) );
  }
}

TEST_CASE( "a fourth quadrant vector" )
{
  SECTION( "plus a fourth quadrant vector" )
  {
    float seven_pi_over_four = 7 * M_PI / 4;
    float eleven_pi_over_six = 11 * M_PI / 6;

    unique_ptr<Vector2<Force>> first_vector2 = make_unique<Vector2<Force>>( 10, seven_pi_over_four );    
    unique_ptr<Vector2<Force>> second_vector2 = make_unique<Vector2<Force>>( 20, eleven_pi_over_six );
    
    unique_ptr<Vector2<Force>> result = *first_vector2 + ( *second_vector2 );

    REQUIRE( withinEpsilon( result -> get_magnitude(), 29.7719 ) );
    REQUIRE( withinEpsilon( result -> get_theta(), 5.6725 ) );
  }
}
