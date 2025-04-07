CC 				:= g++
FLAGS	 		:= 	-Wall -Wextra -Wpedantic -fpermissive -O2 -DDEBUG -g -fsanitize=address -D_FORTIFY_SOURCE=2 \
					-Ilib/sfml/include -Llib/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

MAIN_SRC_DIR	:= src
SRC_DIRS		:= $(shell find $(MAIN_SRC_DIR)/ -type d)
SRC_DIRS		:= $(SRC_DIRS:%/=%)
SOURCES			:= $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
SOURCES  		:= $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

INCLUDES 		:= $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.h))

MAIN_OBJ_DIR	:= obj
OBJ_DIRS 		:= $(SRC_DIRS:$(MAIN_SRC_DIR)%=$(MAIN_OBJ_DIR)%)
OBJECTS  		:= $(SOURCES:$(MAIN_SRC_DIR)/%.cpp=$(MAIN_OBJ_DIR)/%.o)

BIN      		:= mandelbrot

I_FLAGS    		:= $(SRC_DIRS:%=-I%)
COMP_FLAGS 		:= $(FLAGS) $(I_FLAGS) $(add_flags)
LINK_FLAGS 		:= $(FLAGS)

all: $(BIN)

$(BIN): $(OBJECTS)
	@$(CC) $(LINK_FLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(MAIN_OBJ_DIR)/%.o: $(MAIN_SRC_DIR)/%.cpp $(INCLUDES) | $(OBJ_DIRS)
	@$(CC) -c $(COMP_FLAGS) $< -o $@

$(OBJ_DIRS): %:
	@mkdir $@

run: $(BIN)
	@./$(BIN)


clean: clean_obj clean_bin

clean_obj:
	-rm -r $(MAIN_OBJ_DIR)/*

clean_bin:
	-rm $(BIN)
