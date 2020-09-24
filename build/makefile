CXX = clang++
SDL_INCLUDE = -I/usr/include/SDL2
INC_INCLUDE = -I../src/inc -I../src/inc/input
CXX_FLAGS = -Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++17 -g $(SDL_INCLUDE) $(INC_INCLUDE)
LINKER_FLAGS = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread
OBJ_FILES = engine.o game_renderer.o easy_sdl.o sprite.o point.o input_event.o input_handler.o 
VPATH = ../src/main:../src/main/input

all: Allengine cscope

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $<

Allengine: $(OBJ_FILES) main.o
	$(CXX) $(LINKER_FLAGS) -o Allengine $(OBJ_FILES) main.o

.PHONY: clean

clean:
	-rm *.o Allengine

.DELETE_ON_ERROR:

cscope:
	cd ~/Games/Allengine && find . -name "*.h" > cscope.files && \
	find . -name "*.cpp" >> cscope.files && cscope -b -q -k -R
