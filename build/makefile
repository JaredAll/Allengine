CXX = clang++
SDL_INCLUDE = -I/usr/include/SDL2
INC_INCLUDE = -I../src/inc -I../src/inc/input -I../src/inc/physics -I../test/inc
CXX_FLAGS = -Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++17 -g $(SDL_INCLUDE) $(INC_INCLUDE)
LINKER_FLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread
OBJ_FILES = engine.o game_renderer.o easy_sdl.o sprite.o point.o input_event.o input_handler.o \
world_coordinates.o screen_coordinates.o screen_window.o physics_component.o physics_handler.o \
physics_ball.o
TEST_OBJ_FILES = test_driver.o vector2_test.o physics_ball_test.o \
physics_ball_collision_test.o physics_ball_input_test.o test_component_factory.o
VPATH = ../src/main:../src/main/input:../src/main/physics:../test/main

all: Allengine tests cscope

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $<

Allengine: $(OBJ_FILES) main.o
	$(CXX) $(LINKER_FLAGS) -o Allengine $(OBJ_FILES) main.o

tests: $(TEST_OBJ_FILES) $(OBJ_FILES)
	$(CXX) $(LINKER_FLAGS) -o tests $(TEST_OBJ_FILES) $(OBJ_FILES)

.PHONY: clean

clean:
	-rm *.o Allengine tests

.DELETE_ON_ERROR:

cscope:
	cd ~/Games/Allengine && find . -name "*.h" > cscope.files && \
	find . -name "*.cpp" >> cscope.files && cscope -b -q -k -R
