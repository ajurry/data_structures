INCLUDE_DIR = include
SOURCE_DIR = source

SRC = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJ = $(SRC:.cpp = .o)

CXX = g++
DEBUG = -g
CXXFLAGS = -Wall -I$(INCLUDE_DIR) -std=c++11
LFLAGS = -Wall $(DEBUG) -std=c++11

test: $(OBJ)
	$(CXX) -o $@ $^ $(LFLAGS)

.PHONY: clean
clean:
	rm -f test