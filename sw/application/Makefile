SRC = $(wildcard *.cpp)

CC = g++

COMPILER_FLAGS = -w -Wall -O3 -pg

#LINKER_FLAGS = -lsfml-window -lsfml-graphics -lsfml-system
LINKER_FLAGS = -lSDL2

OBJ_NAME = main_serial

all: $(OBJS)
	$(CC) $(SRC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
