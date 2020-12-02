cmake_minimum_required(VERSION 3.10)

project(Allengine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(
  tests
  
  ../../src/main/world_coordinates.cpp
  ../../src/main/screen_coordinates.cpp
  ../../src/main/game_renderer.cpp
  ../../src/main/sprite.cpp
  ../../src/main/point.cpp
  ../../src/main/engine.cpp
  ../../src/main/screen_window.cpp
  # ../../src/main/main.cpp
  ../../src/main/easy_sdl.cpp
  ../../src/main/physics/physics_handler.cpp
  ../../src/main/physics/physics_component.cpp
  ../../src/main/input/input_handler.cpp
  ../../src/main/input/input_event.cpp

  ../../test/main/physics_ball_collision_test.cpp
  ../../test/main/physics_ball.cpp
  ../../test/main/physics_ball_input_test.cpp
  ../../test/main/physics_ball_test.cpp
  ../../test/main/test_component_factory.cpp
  ../../test/main/test_driver.cpp
  ../../test/main/vector2_test.cpp
  )

include_directories(
  ../../src/inc
  ../../src/inc/input
  ../../src/inc/physics
  ../../test/inc/
  )

list(
  APPEND
  CMAKE_MODULE_PATH
  ./sdl2-cmake-modules )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_image_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_ttf_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(
  tests
  SDL2::Main
  SDL2::Image
  SDL2::TTF
  Threads::Threads)
