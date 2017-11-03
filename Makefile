GCC := g++
STATIC_CC := ar

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := lib
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
CXXFLAGS := -Iinclude -std=c++11 -Os
LDFLAGS := 
STATICFLAGS := -r -s 

MKDIR := mkdir -p
RMDIR := rm -rf
RMFILE := rm  -rf

static: directories make_lib clean_lib $(OBJ_FILES)
	$(STATIC_CC) $(STATICFLAGS) $(LIB_DIR)/libfuzzy.a $(OBJFILES)

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

make_lib:
	$(MKDIR) $(LIB_DIR)

clean: clean_obj clean_bin clean_lib

clean_obj:
	$(RMFILE) $(OBJ_DIR)/*

clean_bin:
	$(RMFILE) $(BIN_DIR)/*

clean_lib:
	$(RMFILE) $(LIB_DIR)/*
	
purge:
	$(RMDIR) $(OBJ_DIR)
	$(RMDIR) $(BIN_DIR)
	$(RMDIR) $(LIB_DIR)
	
