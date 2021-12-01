# should work directly on both GNU/Linux and Windows (g++ through mingw)
CC = g++
CC_TOOLS = gcc
EXECUTABLE = jornada_porcaria
CC_FLAGS =-Wall -Wno-missing-braces --std=c++17
LIB_FLAGS =-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
WINDOWS_FLAGS =-lraylib -lopengl32 -lgdi32 -lwinmm
# default directories
SRC_DIR = src
OBJ_DIR = objs

# the directory in which raylib4.0 is present
RAYLIB_DIR = raylib-4.0.0_win64_mingw-w64

# files that're gonna get read/produced by either the compiler or linker
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
DEPS := $(patsubst %.o, %.d, $(OBJS))
EXTRA_DEPS = 

# -p flag doesn't work on windows
MKDIR_COMMAND = mkdir -p $@

# main game compiling logic (including our windows target)
all: $(OBJ_DIR) $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $(EXECUTABLE) $(LIB_FLAGS)

windows: LIB_FLAGS := -static-libgcc -static-libstdc++ \
	-lmingw32 -L./$(RAYLIB_DIR)/lib $(WINDOWS_FLAGS)
windows: CC_FLAGS := $(CC_FLAGS) -Wl,-subsystem,windows
windows: MKDIR_COMMAND = mkdir $@
windows: EXTRA_DEPS := -I./$(RAYLIB_DIR)/include
windows: all

-include $(DEPS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp 
	$(CC) $(CC_FLAGS) -MD -o $@ -c $< $(EXTRA_DEPS)

$(OBJ_DIR):
	$(MKDIR_COMMAND)

# compiling commands for our tools (both editor and launcher)
#
# some variables have to be modified first if we want to compile them for
# windows platforms and such
windows_tools: LIB_FLAGS := -static-libgcc -static-libstdc++ \
		-lmingw32 -L./$(RAYLIB_DIR)/lib $(WINDOWS_FLAGS)
windows_tools: CC_TOOLS += -Wall -Wl,-subsystem,windows
windows_tools: tools


tools: editor launcher
editor: editor/editor.o
	$(CC_TOOLS) editor/editor.o -o mapitor $(LIB_FLAGS)

launcher: launcher/launcher.o
	$(CC_TOOLS) launcher/launcher.o -o launcheiro $(LIB_FLAGS) 

editor/editor.o: editor/editor.c
	$(CC_TOOLS) -c -o $@ $< -I./$(RAYLIB_DIR)/include

launcher/launcher.o: launcher/launcher.c
	$(CC_TOOLS) -c -o $@ $< -I./$(RAYLIB_DIR)/include

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) $(OBJS) $(DEPS) $(EXECUTABLE).exe
	rm -f editor/editor.o mapitor mapitor.exe
	rm -f launcher/launcher.o launcheiro launcheiro.exe

