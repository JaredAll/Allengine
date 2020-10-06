#ifndef JAREDALL_ALLENGINE_VECTOR_QUALITY
#define JAREDALL_ALLENGINE_VECTOR_QUALITY

#include <memory>

template< typename, typename = std::void_t<>>
struct IsIntegratableT : std::false_type
{};

template< typename T>
struct IsIntegratableT< T, std::void_t< typename T::Integration >>
  : std::true_type
{};

struct Displacement
{
};

struct Velocity
{
  using Integration = Displacement;
};

struct Acceleration
{
  using Integration = Velocity;
};

struct Force
{
};

#endif
