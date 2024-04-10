/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:40:20 by avialle-          #+#    #+#             */
/*   Updated: 2024/04/10 11:23:44 by avialle-         ###   ########.fr       */
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
# define ERR_ARGS "Error : Invalid number of arguments.\n"
# define ERR_UNAVAILABLE_ENV "Minishell: Environment unavailable.\n"
# define ERR_MALLOC "Minishell: Allocation error\n"
# define ERR_QUOTES "Minishell: open quotes are not interpreted.\n"
# define ERR_INFILE "Minishell: open quotes are not interpreted.\n"
# define ERR_PARENTHESIS "Minishell: \
open parenthesis are not interpreted.\n"
# define ERR_OPEN_PIPE "Minishell: open pipe are not interpreted.\n"
# define ERR_OPEN_LOGICAL_OP "Minishell: \
open logical operators are not interpreted.\n"
# define ERR_WRONG_CHAR "Minishell: uninterpreted token \
present outside quotes.\n"
# define ERR_NEAR_TOKEN "Minishell: syntax error near unexpected token"
# define ERR_STAR_TOKEN "Minishell: *: ambiguous redirect\n"
# define ERR_EOF_UNEXPECTED "Minishell: syntax error: unexpected end of file.\n"
# define ERR_EOF_HEREDOC "Minishell:\
 warning: here-document at line 1 delimited by end-of-file"
# define ERR_PWD "pwd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory"
# define ERR_SHLVL "minishell: warning: shell level (%d) too high, \
resetting to 1"
# define ERR_HEREDOC "%sMinishell: warning: here-document \
at line %d delimited by end-of-file (wanted `%s')%s\n"
# define ERR_DOT ": filename argument required\n.: \
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
	PARENTHESE
}	t_tkntype;

/*
All structures are contained in minishell structure
*/

typedef struct s_io
{
	int	fd_in;
	int	fd_out;
}	t_io;

/*
All structures are contained in minishell structure
*/

typedef struct s_btree
{
	char			**cmds;
	int				branch;
	t_tkntype		type;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

/*
All structures are contained in minishell structure
*/

typedef enum e_error
{
	NOTHING = -1,
	MALLOC_E,
	FILE_E,
	TYPE_E
}	t_error;

/*
All structures are contained in minishell structure
*/

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

/*
All structures are contained in minishell structure
*/

typedef struct tkn_list
{
	struct s_token	*head;
	struct s_token	*tail;
}	t_tknlist;

/*
All structures are contained in minishell structure
*/

typedef struct e_env
{
	char			*value;
	int				secret;
	struct s_env	*next;
}	t_env;

/*
All structures are contained in minishell structure
*/

typedef struct s_shell
{
	t_env		*env;
	t_tknlist	*tknlist;
	t_btree		*btree;
	t_io		*io_global;
	int			last_gstatus;
}	t_shell;

#endif