# Project Makefile

CC = gcc
CFLAGS = -Iinclude -Wall
SRC_DIR = src
OBJ_DIR = lib
BIN_DIR = bin
LOG_DIR = log

SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/file_operations.c \
          $(SRC_DIR)/directory_operations.c \
          $(SRC_DIR)/permissions.c \
          $(SRC_DIR)/logger.c

OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/file_operations.o \
          $(OBJ_DIR)/directory_operations.o \
          $(OBJ_DIR)/permissions.o \
          $(OBJ_DIR)/logger.o

EXECUTABLE = $(BIN_DIR)/program.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

