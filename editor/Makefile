# Makefile that I've made in order to ease the compiling process of our map
# editor
CC=gcc
LIB_FLAGS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
EXEC_NAME=mapitor

all: editor.o
	$(CC) editor.o -o $(EXEC_NAME) $(LIB_FLAGS)

editor.o : editor.c

.PHONY: clean

clean:
	rm $(EXEC_NAME) editor.o

