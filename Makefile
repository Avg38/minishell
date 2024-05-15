.DEFAULT_GOAL: $(NAME)
# valgrind --leak-check=full --suppressions=.readline.supp ./minishell
NAME		=	minishell
NAME_BONUS	=	minishell_bonus
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
			src/terminal/signal.c\
			\
			src/utils/ft_exit.c\
			src/utils/print_tree.c\
			src/utils/utils_tknlist1.c\
			src/utils/utils_tknlist2.c\
			src/utils/utils_tknlist3.c\
			src/utils/utils_tkntype.c\
			\
			src/main.c

SRC_BONUS	=	src_bonus/builtins/cd.c\
				src_bonus/builtins/echo.c\
				src_bonus/builtins/env.c\
				src_bonus/builtins/exit.c\
				src_bonus/builtins/export.c\
				src_bonus/builtins/pwd.c\
				src_bonus/builtins/unset.c\
				\
				src_bonus/env/env_handler.c\
				src_bonus/env/env_sort.c\
				src_bonus/env/env_utils.c\
				\
				src_bonus/exec/browse_heredoc.c\
				src_bonus/exec/browse_node.c\
				src_bonus/exec/browse_tree.c\
				src_bonus/exec/exec_bin.c\
				src_bonus/exec/exec_builtins.c\
				src_bonus/exec/exec_handler.c\
				src_bonus/exec/get_path.c\
				\
				src_bonus/lexer/handle_token1.c\
				src_bonus/lexer/handle_token2.c\
				src_bonus/lexer/lexer_utils.c\
				src_bonus/lexer/lexer.c\
				\
				src_bonus/libft_extension/libft_extension1.c\
				src_bonus/libft_extension/libft_extension2.c\
				src_bonus/libft_extension/libft_extension3.c\
				\
				src_bonus/parser/binary_tree/bin_tree.c\
				src_bonus/parser/binary_tree/bin_tree_utils.c\
				src_bonus/parser/expander/expand_dollars.c\
				src_bonus/parser/expander/expand_wildcards.c\
				src_bonus/parser/expander/expander.c\
				src_bonus/parser/linker/linker.c\
				src_bonus/parser/reducer/reducer.c\
				src_bonus/parser/tknlist_handler/tknlist_reorder1.c\
				src_bonus/parser/tknlist_handler/tknlist_reorder2.c\
				src_bonus/parser/parser.c\
				src_bonus/parser/verify_syntax.c\
				\
				src_bonus/terminal/loop.c\
				src_bonus/terminal/prompt.c\
				src_bonus/terminal/signal.c\
				\
				src_bonus/utils/ft_exit.c\
				src_bonus/utils/print_tree.c\
				src_bonus/utils/utils_tknlist1.c\
				src_bonus/utils/utils_tknlist2.c\
				src_bonus/utils/utils_tknlist3.c\
				src_bonus/utils/utils_tkntype.c\
				\
				src_bonus/main.c

OBJ			=	$(SRC:.c=.o)
OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = libft/libft.a
_CLEAR	= \033[0K\r\c
_OK	= [\033[32mOK\033[0m]

all : force $(NAME)

bonus : force $(NAME_BONUS)

$(LIBFT_A):	libft/libft.h
	@echo "[..] libft... compiling \r\c"
	@$(MAKE) -C $(LIBFT_DIR) -s
	@echo "$(_CLEAR)"

$(NAME):	$(OBJ) $(LIBFT_A)
	@${CC} ${CFLAGS} -g3 -I include -I libft/ -o $@ $^ -Llibft -lft -lreadline
	@echo "$(_OK) $(NAME) compiled"

${NAME_BONUS}: ${OBJ_BONUS} $(LIBFT_A)
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

reb : fclean bonus

.PHONY: all bonus clean fclean re reb force