GCC := g++

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
CXXFLAGS := -Iinclude -std=c++11 -Os
LDFLAGS := 

MKDIR := mkdir -p
RMDIR := rm -rf
RMFILE := rm 

all: directories fuzzy

fuzzy: main $(OBJ_FILES)
	$(GCC) -o $(BIN_DIR)/$@ $(OBJ_DIR)/main.o $(OBJ_FILES) $(LDFLAGS)

main:
	$(GCC) $(CXXFLAGS) -c main.cpp -o $(OBJ_DIR)/main.o
	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(GCC) $(CXXFLAGS) -c $< -o $@

directories:
	$(MKDIR) $(OBJ_DIR)
	$(MKDIR) $(BIN_DIR)

clean:
	$(RMFILE) $(OBJ_DIR)/*
	$(RMFILE) $(BIN_DIR)/*
	
purge:
	$(RMDIR) $(OBJ_DIR)
	$(RMDIR) $(BIN_DIR)
	
