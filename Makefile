.DEFAULT_GOAL: all

NAME = minishell

SRC		=	\
			src/builtins/cd.c\
			src/builtins/echo.c\
			src/builtins/env.c\
			src/builtins/exit.c\
			src/builtins/export.c\
			src/builtins/pwd.c\
			src/builtins/unset.c\
			\
			src/env/env_handler.c\
			src/env/env_sort.c\
			src/env/env_utils.c\
			\
			src/exec/browse_heredoc.c\
			src/exec/browse_node.c\
			src/exec/browse_tree.c\
			src/exec/exec_bin.c\
			src/exec/exec_builtins.c\
			src/exec/exec_handler.c\
			src/exec/get_path.c\
			\
			src/lexer/handle_token.c\
			src/lexer/handle_token2.c\
			src/lexer/lexer_utils.c\
			src/lexer/lexer.c\
			\
			src/libft_extension/libft_extension1.c\
			src/libft_extension/libft_extension2.c\
			src/libft_extension/libft_extension3.c\
			\
			src/parser/binary_tree/bin_tree.c\
			src/parser/binary_tree/bin_tree_utils.c\
			src/parser/expander/expand_dollars.c\
			src/parser/expander/expand_wildcard.c\
			src/parser/expander/expander.c\
			src/parser/linker/linker.c\
			src/parser/expander/expander.c\
			src/parser/reducer/reducer.c\
			src/parser/tknlist_handler/tknlist_recorder1.c\
			src/parser/tknlist_handler/tknlist_recorder2.c\
			src/parser/parser.c\
			src/parser/verify_syntax.c\
			\
			src/terminal/loop.c\
			src/terminal/prompt.c\
			\
			src/utils/ft_exit.c\
			src/utils/utils_tknlist1.c\
			src/utils/utils_tknlist2.c\
			src/utils/utils_tknlist3.c\
			src/utils/utils_tkntype.c\
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

all:		force $(NAME)

$(NAME):	$(OBJ) libft/libft.a
		echo "$(MESSAGE_COMPILE)"
		$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LINKS) -o $(NAME)
		echo "$(MESSAGE_DONE)"

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
		mkdir -p $(OBJDIR)/parser/binary_tree
		mkdir -p $(OBJDIR)/parser/expander
		mkdir -p $(OBJDIR)/parser/linker
		mkdir -p $(OBJDIR)/parser/reducer
		mkdir -p $(OBJDIR)/parser/tknlist_handler
		mkdir -p $(OBJDIR)/terminal
		mkdir -p $(OBJDIR)/utils

clean:
		echo "$(MESSAGE_CLEAN)"
		$(RM) $(OBJDIR)
		make clean -C libft
		echo "$(MESSAGE_CLEAN_DONE)"

fclean:		clean
		$(RM) $(NAME)
		make fclean -C libft

force:
		make -C libft -s

re:		fclean all

.PHONY: all clean fclean force re