CC := g++
MAIN_FLAGS := -Wall -Wextra -Wpedantic -fpermissive -O2 -DDEBUG -g -fsanitize=address -D_FORTIFY_SOURCE=2
ADD_FLAGS  := -Ilib/sfml/include -Llib/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

MAIN_SRC_DIR := src
SRC_DIRS 	 := $(MAIN_SRC_DIR)/ $(wildcard $(MAIN_SRC_DIR)/*/)
SRC_DIRS 	 := $(SRC_DIRS:%/=%)
MAIN_OBJ_DIR := obj
OBJ_DIRS 	 := $(SRC_DIRS:$(MAIN_SRC_DIR)%=$(MAIN_OBJ_DIR)%)

SOURCES  := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
INCLUDES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.h))
OBJECTS  := $(SOURCES:$(MAIN_SRC_DIR)/%.cpp=$(MAIN_OBJ_DIR)/%.o)
BIN      := mandelbrot

DOCS_NAME := docs_config

I_FLAGS    := -I$(MAIN_SRC_DIR)
COMP_FLAGS := $(MAIN_FLAGS) $(ADD_FLAGS) $(I_FLAGS)
LINK_FLAGS := $(MAIN_FLAGS) $(ADD_FLAGS)

all: $(BIN)

$(BIN): $(OBJECTS)
	@$(CC) $(LINK_FLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(MAIN_OBJ_DIR)/%.o: $(MAIN_SRC_DIR)/%.cpp $(INCLUDES) | $(OBJ_DIRS)
	@$(CC) -c $(COMP_FLAGS) $< -o $@

$(OBJ_DIRS): %:
	@mkdir $@

run: $(BIN)
	@./$(BIN)

docs:
	@doxygen $(DOCS_NAME)


clean: clean_obj clean_bin

clean_obj:
	-rm -r $(MAIN_OBJ_DIR)/*

clean_bin:
	-rm $(BIN)
