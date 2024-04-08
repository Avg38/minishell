/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:40:20 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/08 14:04:53 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>

// COLORS
# define RESET	"\x1b[0m"
# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32m"
# define BLUE	"\x1b[34m"
# define PINK	"\x1b[35m"
# define YELLOW	"\x1b[33m"
# define CYAN	"\x1b[36m"

// FD
# define FD_READ 0
# define FD_WRITE 0
# define FD_IN 0
# define FD_OUT 0

// MESSAGE
# define ARGS_ERR_MSG "Error : Invalid number of arguments.\n"
# define UNAVAILABLE_ENV "Minishell: Environment unavailable.\n"
# define MALLOC_ERR_MSG "Minishell: Allocation error\n"
# define QUOTES_ERR_MSG "Minishell: open quotes are not interpreted.\n"
# define INFILE_ERR_MSG "Minishell: open quotes are not interpreted.\n"
# define PARENTHESIS_ERR_MSG "Minishell: \
open parenthesis are not interpreted.\n"
# define OPEN_PIPE_ERR_MSG "Minishell: open pipe are not interpreted.\n"
# define OPEN_LOGICAL_OP_ERR_MSG "Minishell: \
open logical operators are not interpreted.\n"
# define WRONG_CHAR_ERR_MSG "Minishell: uninterpreted token \
present outside quotes.\n"
# define NEAR_TOKEN_ERR_MSG "Minishell: syntax error near unexpected token"
# define STAR_TOKEN_ERR_MSG "Minishell: *: ambiguous redirect\n"
# define UNEXPECTED_EOF "Minishell: syntax error: unexpected end of file.\n"
# define EOF_HEREDOC "Minishell:\
 warning: here-document at line 1 delimited by end-of-file"
# define PWD_ERR_MSG "pwd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory"
# define SHLVL_ERR_MSG "minishell: warning: shell level (%d) too high, \
resetting to 1"
# define HEREDOC_MSG "%sMinishell: warning: here-document \
at line %d delimited by end-of-file (wanted `%s')%s\n"
# define DOT_MSG_ERR ": filename argument required\n.: \
usage: . filename [arguments]\n"

extern int	g_status;

typedef enum e_id_gc
{
	TKN_LIST = 1,
	B_TREE,
	ENV,
	TMP
}	t_id_gc;

typedef enum e_tkntype
{
	WORD,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	PIPE,
	AND,
	OR,
	S_QUOTE,
	D_QUOTE,
	LEFT_P,
	PARENTHESIS
}	t_tkntype;

typedef struct s_io
{
	int	fd_in;
	int	fd_out;
}	t_io;

typedef struct s_btree
{
	char			**cmds;
	int				branch;
	t_tkntype		type;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef enum e_error
{
	NOTHING = -1,
	MALLOC_E,
	FILE_E,
	TYPE_E
}	t_error;

typedef struct s_token
{
	t_tkntype		type;
	char			*content;
	int				link;
	size_t			index;
	int				priority;
	int				used_flag;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct tkn_list
{
	struct s_token	*head;
	struct s_token	*tail;
}	t_tknlist;

typedef struct e_env
{
	char			*value;
	int				secret;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	t_env		*env;
	t_tknlist	*tknlist;
	t_btree		*btree;
	t_io		*io_global;
	int			last_gstatus;
}	t_mini;

#endif