# Allengine

A generalization of the engine used in JaredAll/Tetris. This project
extends that educational project with versatility in mind. This engine
is intended to be able to run any two dimensional game.

# Intent

This project is another playground in which to make software
engineering decisions, good or bad, and leverage C++'s dynamic and
static polymorphism. However, the challenge is greater here than in
Tetris. Designing a game engine that can run any game requires more
thought and care than one that is suited to only a single game.

# Design

## Engine

The `Engine` class orchestrates the Allengine runtime. It is responsible
for creating and maintaining the SDL window, keeping the frame timer,
updating game components, handling input, and calling the
renderer. The `advance` function template is used to advance the game
for a single frame, and is SFINAE'd away if called with a vector of
anything other than `GameComponents`. The instantiation for that type
also includes the instantiation for the private methods
`render_components` and `update_components`; check out my blog,
jaredall.dev, for a deeper explanation of the `Engine` architecture.

## Physics

The Allengine incorporates rudimentary two dimensional physics using
the `PhysicsComponent` and `PhysicsHandler` classes. The details of
the physical interactions handled by the `PhysicsHandler` themselves
comprise the `Vector2` class. The class uses a magnitude and angle to
represent a vector. It is also a template with three different
specializations based upon the type traits the template parameter
exhibits. The first is the default specialization, which only
implements vector addition. The second specialization is for those
`Quality`s that have been specified as *integratable*. This
specialization includes an `integrate(delta_t)` method that returns a
`Vector2` parametrized by the `Quality` specified in the integrated
`Quality`'s definition. This allows the type representations to
reflect how the qualities of interpreting an integration are
determined in real life. For example, integrating a velocity equation
yields a displacement equation. The third specialization simply
expands upon that idea with an `integrate2` method, allowing one to go
directly from an acceleration vector to a displacement vector. By
making the `Vector2`s typed we decrease the chances of using two
different qualities in a calculation. It should be noted that these
integrate methods assume that the acceleration is constant; however,
for small `delta_t`, repeated integrations should approximate a
changing acceleration.

# Build

I have added CMake compatibility for the Allengine tests
executable. The tests executable will run a small example game using
the Allengine. Running the Allengine tests requires PThreads, SDL2,
SDL2\_Image, and SDL2\_TTF. The CMakeLists.txt file is under the
/build/cmake/ directory.
