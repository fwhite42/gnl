NAME			:= libgnl.a
BUFF_SIZE_VAL	:= 1

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
CC				:= gcc
CC_FLAGS		:= -Wall -Werror -Wextra
NO_LINK			:= -c
LINK_GNL		:= -L. -lgnl
HEADERS			:= -I$(SRC_DIR)
BUFF_SIZE		:= -D BUFFER_SIZE=$(BUFF_SIZE_VAL)
COMPILE			:= $(CC) $(BUFF_SIZE) $(CC_FLAGS) $(NO_LINK) $(HEADERS)
# Archive settings
ARCHIVE			:= ar -rc

# Make rules

$(OBJ_DIR)	:
	@mkdir $(OBJ_DIR)

$(OBJECTS):$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.c $(OBJ_DIR)
	@$(COMPILE) $< -o $@

$(NAME): $(OBJECTS)
	@$(ARCHIVE) $(NAME) $(OBJECTS)
	@$(MAKE) clean

bonus : $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm libgnl.a
	@rm *.exe

$(TEST_FILE_NAMES):%: $(TEST_DIR)/%.c $(NAME)
	@gcc $(HEADERS) $(LINK_GNL) $< -o run_test.exe
.PHONY: objects clean archive fclean $(TEST_FILE_NAMES)
