CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -pthread -lglfw -lGLU -lGL -lGLEW

INCDIR = -I/usr/include -Ilib/ -Iinclude/imgui -Isrc/
LIBDIR = -L/usr/lib

SRC = $(shell find -wholename "*.cpp")

OUT = build/prog

OBJ = $(SRC:.cpp=.o)
vpath %.cpp src

$(OUT): $(OBJ)
	@$(CXX) $(OBJ) -o $(OUT) $(LIBDIR) $(LDFLAGS)

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(INCDIR) -c $< -o $@

clean:
	@rm -f $(OBJ) $(OUT)

run: clean $(OUT)
	@$(OUT)

r:
	@$(OUT)

.PHONY: clean
