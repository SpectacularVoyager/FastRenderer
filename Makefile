CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -pthread -lglfw -lGLU -lGL -lGLEW

INCDIR = -I/usr/include -Ilib/
LIBDIR = -L/usr/lib

SRC = $(shell find -wholename "./src/*.cpp")

OUT = build/prog

OBJ = $(SRC:.cpp=.o)

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
