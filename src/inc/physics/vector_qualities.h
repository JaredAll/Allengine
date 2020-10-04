#ifndef JAREDALL_ALLENGINE_VECTOR_QUALITY
#define JAREDALL_ALLENGINE_VECTOR_QUALITY

#include <memory>

template< typename, typename = std::void_t<>>
struct IsIntegratableT : std::false_type
{};

template< typename T>
struct IsIntegratableT< T, std::void_t< decltype( std::declval<T>().get_integration())>>
  : std::true_type
{
  bool value = true;
};

struct Displacement
{
};

struct Velocity
{
  Displacement get_integration();
};

struct Acceleration
{
  Velocity get_integration();
};

struct Force
{
  Velocity get_integration();
};

#endif
