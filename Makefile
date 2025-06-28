# Diretórios
SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
DEBUG_DIR := $(BIN_DIR)/debug
RELEASE_DIR := $(BIN_DIR)/release

CXX := g++
CXXFLAGS := -std=c++20 -m64 -Wall -I$(INC_DIR)
LDFLAGS := -lSDL2 -lSDL2main -lSDL2_image

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=%.o)

.PHONY: all debug release clean run-debug run-release

all: debug

debug: CXXFLAGS += -g
debug: DIR := $(DEBUG_DIR)
debug: $(DEBUG_DIR)/main

release: CXXFLAGS += -O3 -s
release: DIR := $(RELEASE_DIR)
release: $(RELEASE_DIR)/main

$(DEBUG_DIR)/main $(RELEASE_DIR)/main: $(OBJECTS)
	@mkdir -p $(DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run-debug: debug
	./$(DEBUG_DIR)/main

run-release: release
	./$(RELEASE_DIR)/main

clean:
	rm -f *.o
	rm -rf $(DEBUG_DIR) $(RELEASE_DIR)

