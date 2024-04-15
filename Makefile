.DEFAULT_GOAL: all

NAME = minishell

SRC		=	\
			src/builtins/cd.c\
			src/builtins/echo.c\
			src/builtins/exit.c\
			src/builtins/export.c\
			\
			src/env/env_handler.c\
			src/env/env_sort.c\
			src/env/env_utils.c\
			\
			src/lexer/handle_token.c\
			src/lexer/handle_token2.c\
			src/lexer/lexer_utils.c\
			src/lexer/lexer.c\
			\
			src/parser/parser.c\
			\
			src/terminal/loop.c\
			src/terminal/prompt.c\
			\
			src/utils/ft_exit.c\
			\
			src/main.c


OBJDIR	=	obj
OBJ		=	$(patsubst src/%.c, obj/%.o, $(SRC))


CC			=	gcc -g
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-Iinclude -Ilibft
LINKS		=	-Llibft -lft
RM			=	rm -rf

# Colors
COLOR_RESET			=	\033[0m
COLOR_RED			=	\033[0;31m
COLOR_GREEN			=	\033[0;32m
COLOR_PURPLE		=	\033[0;95m
COLOR_BLUE			=	\033[0;34m

# Colored Messages
MESSAGE_COMPILE		=	$(COLOR_BLUE)Compiling the program...$(COLOR_RESET)
MESSAGE_DONE		=	$(COLOR_GREEN)Compilation completed.$(COLOR_RESET)
MESSAGE_CLEAN		=	$(COLOR_PURPLE)Cleaning up...$(COLOR_RESET)
MESSAGE_CLEAN_DONE	=	$(COLOR_PURPLE)Cleanup completed.$(COLOR_RESET)

all:	force $(NAME)

$(NAME):
		@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LINKS) -o $(NAME)
# @echo $(MESSAGE_COMPILE)
# @echo $(MESSAGE_DONE)

obj/%.o:	src/%.c include/minishell.h libft/libft.h Makefile | $(OBJDIR)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR):
		mkdir -p $(OBJDIR)
		mkdir -p $(OBJDIR)/builtins
		mkdir -p $(OBJDIR)/env
		mkdir -p $(OBJDIR)/exec
		mkdir -p $(OBJDIR)/lexer
		mkdir -p $(OBJDIR)/libft_extension
		mkdir -p $(OBJDIR)/parser
		mkdir -p $(OBJDIR)/terminal
		mkdir -p $(OBJDIR)/utils

clean:
		echo $(MESSAGE_CLEAN)
		@$(RM) $(OBJDIR)
		@make clean -C libft
		echo $(MESSAGE_CLEAN_DONE)

fclean:
		@$(RM) $(NAME)
		@make fclean -C libft

force:
		@make -C libft -s

re:		fclean all

.PHONY: all clean fclean force re