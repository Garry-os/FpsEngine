CXX = clang++
CXXFLAGS = -Wall -Wextra -O2 -std=c++23 -MMD -MP

CC = clang
CFLAGS = -Wall -Wextra -O2 -std=c23 -MMD -MP

## Includes
CXXFLAGS += -I libs/glad/include -I src

LINKLIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

BIN = bin
SRC = $(shell find src -name "*.cpp")
OBJ = $(patsubst src/%.cpp, $(BIN)/%.o, $(SRC))

.PHONY: all clean

all: dirs game run
build: dirs game

dirs:
	@ mkdir -p $(BIN)
	@ mkdir -p $(BIN)/engine
	@ mkdir -p $(BIN)/engine/renderer

run:
	@ $(BIN)/game

game: $(OBJ) $(BIN)/glad.o
	$(CXX) -o $(BIN)/game $^ $(LINKLIBS)

$(BIN)/glad.o: libs/glad/src/glad.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN)

-include $(OBJ:.o=.d)

