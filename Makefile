NAME			:=	libgnl.a

# Silence All Errors
SILENT			:=	2> /dev/null || true

# Variables
## File Names
SRC_FILE_NAMES	:= get_next_line get_next_line_utils
TEST_FILE_NAMES := test
## Directory Names
OBJ_DIR			:= obj
SRC_DIR			:= src
TEST_DIR		:= tests

# Make targets
FILES			:= $(SRC_FILE_NAMES:%=$(SRC_DIR)/%.c)
OBJECTS			:= $(FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_FILES		:= $(TEST_FILE_NAMES:%=$(TEST_DIR)/%.c)

# Compiler settings
COMPILE			:= gcc
COMPILE_FLAGS	:= -Wall -Werror -Wextra
DONT_LINK		:= -c
LINK_GNL		:= -L. -lgnl
HEADERS			:= -I$(SRC_DIR)
# Archive settings
ARCHIVE			:= ar -rc

# Make rules

temp:
	echo $(FILES)
	echo $(OBJECTS)

$(OBJ_DIR)	:
	@mkdir $(OBJ_DIR)

$(OBJECTS):$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(OBJ_DIR)
	@$(COMPILE) $(COMPILE_FLAGS) $(DONT_LINK) $(HEADERS) $< -o $@

$(NAME): $(OBJECTS)
	@$(ARCHIVE) $(NAME) $(OBJECTS)
	@$(MAKE) clean

clean:
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm libgnl.a

$(TEST_FILE_NAMES):%: $(TEST_DIR)/%.c $(NAME)
	@gcc $(HEADERS) $(LINK_GNL) $< -o run_test.exe
	@./run_test.exe $(SILENT)
	@rm -rf ./run_test.exe $(SILENT)
.PHONY: objects clean archive fclean $(TEST_FILE_NAMES)