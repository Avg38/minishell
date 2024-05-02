/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avialle- <avialle-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:01:50 by avialle-          #+#    #+#             */
/*   Updated: 2024/05/02 16:02:21 by avialle-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

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
# define FD_READ	0
# define FD_WRITE	1
# define FD_IN		0
# define FD_OUT		1

// MESSAGE
# define ERR_ARGS "Error : Invalid number of arguments.\n"
# define ERR_ARGS_ENV "env: '%s': No such file or directory\n"
# define ERR_UNAVAILABLE_ENV "Minishell: Environment unavailable.\n"
# define ERR_MALLOC "Minishell: Allocation error\n"
# define ERR_QUOTES "Minishell: open quotes are not interpreted.\n"
# define ERR_INFILE "Minishell: open quotes are not interpreted.\n"
# define ERR_BRACKETS "Minishell: open brackets are not interpreted.\n"
# define ERR_OPEN_PIPE "Minishell: open pipe are not interpreted.\n"
# define ERR_OPEN_LOGICAL_OP "Minishell: open logical \
	operators are not interpreted.\n"
# define ERR_WRONG_CHAR "Minishell: uninterpreted token \
	present outside quotes.\n"
# define ERR_NEAR_TOKEN "Minishell: syntax error near unexpected token"
# define ERR_STAR_TOKEN "Minishell: *: ambiguous redirect\n"
# define ERR_EOF_UNEXPECTED "Minishell: syntax error: unexpected end of file.\n"
# define ERR_EOF_HEREDOC "Minishell:warning: here-document \
	at line 1 delimited by end-of-file"
# define ERR_PWD "pwd: error retrieving current directory: \
	getcwd: cannot access parent directories: No such file or directory"
# define ERR_SHLVL "minishell: warning: shell level (%d) \
	too high, resetting to 1"
# define ERR_HEREDOC "%sMinishell: warning: here-document \
	at line %d delimited by end-of-file (wanted `%s')%s\n"
# define ERR_DOT ": filename argument required\n.: usage: \
	. filename [arguments]\n"

extern int	g_status;

typedef enum e_gc_id
{
	TKN_LIST = 1,
	B_TREE,
	ENV,
	TMP
}	t_gc_id;

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
	BRACKETS,
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
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tknlist
{
	struct s_token	*head;
	struct s_token	*tail;
}	t_tknlist;

typedef struct s_env
{
	char			*value;
	int				secret;
	struct s_env	*next;
}				t_env;

typedef struct s_shell
{
	t_env		*env;
	t_tknlist	*tknlist;
	t_btree		*btree;
	t_io		io_global;
	int			last_gstatus;
}	t_shell;

// ============== BUILTINS ==============
// -------------- cd.c --------------
int				update_oldpwd(t_env **env);
int				update_pwd(t_env **env, int slash);
int				go_to_path(t_env **env);
int				process_cd(char **cmds, t_env **env);
int				cd(char **cmds, t_env **env);
// -------------- echo.c --------------
int				size_cmds(char **cmds);
// static int is_valid_option(char *option);
int				echo(char **cmds, t_io fds);
// -------------- env.c --------------
int				env(t_env *env, t_io fds);
// -------------- exit.c --------------
int				check_limit(int sign, long result, long digit);
int				is_valid_long(const char *str);
int				check_status_code(char *status_code);
int				process_exit(char **cmds, int *exit_status);
int				builtin_exit(t_shell *shell, char **cmds);
// -------------- export.c --------------
int				print_error_export(char *args, int error);
int				env_add(char *value, t_env **env, int mod);
int				export_handler(char *args, t_env **env);
int				ft_export(char **args, t_env **envt, t_io fds);
// -------------- pwd.c --------------
int				pwd(t_io fds, t_env *env);
// -------------- unset.c --------------
int				unset(char **value, t_env **env);

// ============== ENV ==============
// -------------- env_handler.c --------------
void			env_add_back(t_env **env, t_env *new);
void			*env_get_name(char *dest, char *src);
t_env			*env_init(char **env_array);
// -------------- env_sort.c --------------
int				strlen_2d(char **tab);
void			env_sort(char **tab, int len_env);
void			print_export(char **tab, t_io fds);
void			env_print_sorted(t_env *env, t_io fds);
// -------------- env_utils.c --------------
size_t			env_strlen(t_env *env);
char			*env_get_value(t_env *env, const char *var, size_t len);
size_t			size_all_value(t_env *lst);
char			*env_to_str(t_env *lst);
int				is_in_env(t_env *env, char *args);

// ============== EXEC ==============
// -------------- browse_heredoc.c --------------
void			handle_signals_heredoc(char *input, size_t nb_lines, \
	char *delim);
int				readline_heredoc(t_btree *block, char *line, \
	size_t *nb_lines, int fd_pipe[2]);
void			cross_heredoc(t_shell *shell, t_btree *block, \
	t_io io_inherited);
// -------------- browse_node.c --------------
void			cross_input(t_shell *shell, t_btree *block, t_io io_inherited);
void			cross_output(t_shell *shell, t_btree *block, t_io io_inherited);
void			cross_pipe(t_shell *shell, t_btree *block, t_io io_inherited);
void			cross_operator(t_shell *shell, t_btree *block, \
	t_io io_inherited);
int				cross_brackets(t_shell *shell, t_btree *block, \
	t_io io_inherited);
// -------------- browse_tree.c --------------
int				wait_child(pid_t pid);
void			browse_tree(t_shell *shell, t_btree *bloc, t_io io_inherited);
// -------------- exec_bin.c --------------
char			**env_to_char2(t_env *env);
void			exec_process(t_btree *block, t_env *env, t_io fds);
char			*handle_path(t_btree *block, t_env *env);
int				exec_bin(t_env *env, t_btree *block, t_io fds);
// -------------- exec_builtins.c --------------
int				is_builtin(char *command);
int				exec_builtin(t_env **envt, t_btree *block, t_io fds);
int				fork_builtin(t_env **envt, t_btree *block, t_io fds);
// -------------- exec_handler.c --------------
int				exec_handler(t_shell *shell, t_btree *block, t_io fds);
// -------------- get_path.c --------------
char			*ft_strjoin_pipex(char *s1, char *s2, char *sep);
void			check_path(char *cmd, char *path);
char			*check_cmd_path(char *cmd, char *path);
char			**find_path(t_env *env);
char			*get_cmd_path(char *cmd, t_env *env);

// ============== LEXER ==============
// -------------- handle_token.c --------------
int				handle_file(char *buffer, t_tknlist *list, t_tkntype type);
int				handle_pipe(char *buffer, t_tknlist *list);
int				handle_operator(char *buffer, t_tknlist *list, t_tkntype type);
int				handle_s_quote(char *buffer, t_tknlist *list);
int				handle_d_quote(char *buffer, t_tknlist *list);
// -------------- handle_token2.c --------------
int				is_special_char(char c);
int				handle_brackets(char *buffer, t_tknlist *list);
int				handle_word(char *buffer, t_tknlist *list);
// -------------- lexer_utils.c --------------
char			*ft_strndup(char *buffer, int len, t_gc_id id);
int				is_operator(const char c1, const char c2);
int				detect_error_type(const char c);
// -------------- lexer.c --------------
int				handle_error_lexer(int gc_id, char *msg);
int				detect_type(const char c1, const char c2);
void			handle_token(char *buffer, t_tknlist *list, \
	t_tkntype type, int *i);
int				is_only_space(char *buffer);
t_tknlist		*lexer(char *buffer);

// ============== LIBFT_EXTENSION ==============
// -------------- libft_extension1.c --------------
char			*ft_strcut(char const *str, size_t cut_begin, size_t cut_end);
char			*replace_substr(char *str, char *replacement, \
	size_t start, size_t len);
char			*remove_substr(char *str, size_t start, size_t len_toremove);
// -------------- libft_extension2.c --------------
size_t			ft_strlen_utils(const char *str, int (*f)(char));
size_t			ft_strlen_until_char(const char *str, char c);
size_t			ft_strlen_until_not(const char *str, int (*f)(char));
size_t			ft_strlen_until_not_char(const char *str, char c);
int				str_contains_all_subs_ordered(char *str, char **subs);
// -------------- libft_extension3.c --------------
int				char_is_in_str(char c, char *str);
int				ft_strcmp_case_insensitive(char *s1, char *s2);
int				s1_is_s2_suffix(char *s1, char *s2);
bool			s1_is_s2_prefix(char *s1, char *s2);

// ============== PARSER ==============
// -------------- parser.c --------------
void			set_token_index(t_token *cur);
t_btree			*parser(t_shell *shell);
// -------------- verify_syntax.c --------------
int				printfd_err(int fd, int ret, char *err_msg, char *issue);
void			verify_syntax_tknlist(t_tknlist *lst);

// ~~~~~~~~~~~~~~ BINARY_TREE ~~~~~~~~~~~~~~
// -------------- b_tree_utils.c --------------
size_t			count_argc_cmd(t_token *cur);
char			**get_argv_cmd(t_token *cur, size_t argc);
char			**strdup_in_newchar2(char *delimiter);
char			**extract_cmd_argv(t_token *cur);
int				cmd_in_pipe(t_btree *root, int id_branch);
// -------------- b_tree.c --------------
t_token			*find_prio_token(t_token *cur);
t_btree			*place_in_tree(t_btree *node, t_btree *toplace, int index);
t_btree			*btree_new(t_token *tkn_to_convert);
t_btree			*create_bin_tree(t_tknlist *tknlst);

// ~~~~~~~~~~~~~~ EXPANDER ~~~~~~~~~~~~~~
// -------------- expand_dollars.c --------------
t_token			*expand_dollar(t_shell *shell, t_token *tkn_to_expand, \
	t_tknlist *tkn_lst);
// -------------- expand_wildcards.c --------------
t_token			*expand_wildcard(t_token *tkn_toexpand, t_tknlist *tkn_lst);
// -------------- expander.c --------------
void			expander(t_shell *shell, t_tknlist *tknlist);

// ~~~~~~~~~~~~~~ LINKER ~~~~~~~~~~~~~~
// -------------- linker.c --------------
int				is_link_sensitive(t_tkntype type);
void			linker(t_tknlist *tkn_lst);

// ~~~~~~~~~~~~~~ REDUCER ~~~~~~~~~~~~~~
// -------------- reducer.c --------------
int				type_need_reducing(t_tkntype type);
void			reducer(t_token	*tkn);

// ~~~~~~~~~~~~~~ TKNLIST_HANDLER ~~~~~~~~~~~~~~
// -------------- recorder_tknlist.c --------------
void			rearrange_cmd_redir_order(t_tknlist *tknlst);
// -------------- recorder_tknlist2.c --------------
t_token			*return_end_sequence(t_token *begin_seq);
size_t			size_sequence(t_token *begin_seq);

// ============== TERMINAL ==============
// -------------- loop.c --------------
void			clear_loop(void);
void			clear_ctrl_c(int *stdin_cpy, char **line_read);
void			sig_handler(int sigcode);
void			process_shell(t_shell *shell, char *line_read, int *stdin_cpy);
void			prompt_loop(t_shell *shell);
// -------------- prompt.c --------------
char			*create_prompt(t_shell *shell);

// ============== UTILS ==============
// -------------- ft_exit.c --------------
void			free_and_exit(int exit_code);
void			print_and_exit(char *msg, char *color, int exit_code);
void			print_without_exit(char *msg, char *color, int exit_code);
void			print_path_error(char *arg, int exit_code, int error);
void			print_strerror(char *arg, char *color, int new_status);
// -------------- utils_tknlist1.c --------------
t_token			*create_node(t_tkntype typed, char *value, int linked);
int				add_node(t_tknlist *list, t_token *node);
void			init_list(t_tknlist **list);
// -------------- utils_tknlist2.c --------------
void			add_after_another(t_tknlist *list, \
	t_token *tkn1, t_token *tkn2);
void			pop_token_in_place(t_tknlist *list_tkn, t_token *to_pop);
void			add_tknlist_after_target(t_tknlist *lst1, \
	t_token *tkn_flag, t_tknlist *lst2);
void			swap_tokens(t_tknlist *lst, t_token *tkn1, t_token *tkn2);
size_t			tknlist_size(t_tknlist *tknlist);
// -------------- utils_tknlist3.c --------------
void			unbound_token_in_place(t_tknlist *list_tkn, t_token *to_pop);
void			tknlist_addfront(t_token *cur, t_tknlist *tknlist);
void			tknlist_addback(t_token *cur, t_tknlist *tknlist);
// -------------- utils_tkntype.c --------------
int				brackets_is_empty(char *content);
int				tkn_is_logic(t_tkntype tkntype);
int				tkn_is_cmd(t_tkntype tkntype);
int				tkn_is_redir(t_tkntype tkntype);
int				tkn_is_operator(t_tkntype tkntype);
// -------------- print_tree.c --------------
void			depth_first_search(t_btree *node, \
	void (*visit)(t_btree *, int));
void			root_first_search(t_btree *node, void (*visit)(t_btree *, int));
void			display_node(t_btree *node, int depth);

// ============== MAIN ==============
// -------------- main.c --------------
int				main(int ac, char **av, char **envp);
t_shell			*singleton_shell(t_shell *addr_shell);
void			handle_shlvl(t_env *env, int nb);

#endif