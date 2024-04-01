TARGET = program
CC = clang++
CFLAGS = -Wall -Werror
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRC_DIR = src
OBJ_DIR = obj/src
BIN_DIR = bin
SRC = $(wildcard $(SRC_DIR)/main/*.cpp) $(wildcard $(SRC_DIR)/lib/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(SFML_FLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET) $(OBJ_DIR)/lib/*.o $(OBJ_DIR)/main/*.o

.PHONY: all clean