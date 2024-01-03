NAME		:=	libgnl.a

SILENT		:=	2> /dev/null || true
FILES		:=	get_next_line.c												   \
				get_next_line_utils.c

OBJECTS		:=	$(FILES:%.c=%.o)

TEST_FILES	:=	test.c

COMPILE		:=	gcc

DONT_LINK	:=	-c

ARCHIVE		:=	ar -rc

$(OBJECTS): %.o: %.c
	@$(COMPILE) $(DONT_LINK) $< -o $@

$(NAME): archive

objects	: $(OBJECTS)

archive : $(OBJECTS)
	@$(ARCHIVE) $(NAME) $(OBJECTS)
	@$(MAKE) clean

clean:
	@rm a.out			$(SILENT)
	@rm $(OBJECTS)		$(SILENT)
	@rm test.o			$(SILENT)

fclean : clean
	@rm $(NAME)			$(SILENT)

test : $(NAME) $(TEST_FILES)
	@gcc	-L. -lgnl test.c -o test
.PHONY: objects clean archive fclean test
