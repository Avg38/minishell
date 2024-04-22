.DEFAULT_GOAL: $(NAME)

NAME		= minishell
NAME_BONUS	= minishell_bonus
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

SRC		=	src/builtins/cd.c\
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
			src/lexer/handle_token1.c\
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
			src/parser/expander/expand_wildcards.c\
			src/parser/expander/expander.c\
			src/parser/linker/linker.c\
			src/parser/reducer/reducer.c\
			src/parser/tknlist_handler/tknlist_reorder1.c\
			src/parser/tknlist_handler/tknlist_reorder2.c\
			src/parser/parser.c\
			src/parser/verify_syntax.c\
			\
			src/terminal/loop.c\
			src/terminal/prompt.c\
			\
			src/utils/ft_exit.c\
			src/utils/print_tree.c\
			src/utils/utils_tknlist1.c\
			src/utils/utils_tknlist2.c\
			src/utils/utils_tknlist3.c\
			src/utils/utils_tkntype.c\
			\
			src/main.c

OBJ		=	$(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT_A = libft/libft.a
_CLEAR	= \033[0K\r\c
_OK	= [\033[32mOK\033[0m]

all : force $(NAME)

$(LIBFT_A):	libft/libft.h
	@echo "[..] libft... compiling \r\c"
	@$(MAKE) -C $(LIBFT_DIR) -s
	@echo "$(_CLEAR)"

$(NAME):	$(OBJ) $(LIBFT_A)
	@${CC} ${CFLAGS} -g3 -I include -I libft/ -o $@ $^ -Llibft -lft -lreadline
	@echo "$(_OK) $(NAME) compiled"

${NAME_BONUS}: ${OBJS} $(LIBFT_A)
	@${CC} ${CFLAGS} -g3 -I include -I libft/ -o $@ $^ -Llibft -lft -lreadline
	@echo "$(_OK) $(NAME_BONUS) compiled"

%.o: %.c include/minishell.h libft/libft.h
	@echo "[..] $(NAME_SHORT)... compiling $*.c\r\c"
	@${CC} ${CFLAGS} -g3 -Iinclude -Ilibft/ -c $< -o $@
	@echo "$(_CLEAR)"

force:
	@make -C libft -s

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean -s
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_BONUS)

fclean:		clean
	@$(MAKE) -C $(LIBFT_DIR) fclean -s
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

re : fclean all

.PHONY: all clean fclean re force