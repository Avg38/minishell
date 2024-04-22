#include "../../include/minishell.h"

void	clear_loop(void)
{
	gc_clear(TMP, free);
	gc_clear(TKN_LIST, free);
	gc_clear(B_TREE, free);
}

void	clear_ctrl_c(int *stdin_cpy, char **line_read)
{
	if (*line_read)
		free(*line_read);
	*line_read = NULL;
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	clear_loop();
}

/*

*/

void	sig_handler(int sigcode)
{
	if (sigcode == SIGINT)
	{
		close(STDIN_FILENO);
		g_status = 130;
	}
	if (sigcode == SIGQUIT)
		write(2, "\b\b  \033[2D", 8);
	if (sigcode == SIGTSTP)
		write(2, "\b\b  \033[2D", 8);
}

/*
process_shell est la colonne vertebral,
on ajoute la ligne de commande lance dans l'historique,
on tokenise la ligne,
on parse la ligne tokenise pour le stocker dans l'arbre binaire.

*/

// void	print_lexer(t_token *list)
// {
// 	while (list != NULL)
// 	{
// 		ft_printf("content = %s, type  = %d, priority = %d\n", list->content, list->type, list->priority);
// 		list = list->next;
// 	}
	
// }


void	process_shell(t_shell *shell, char *line_read, int *stdin_cpy)
{
	add_history(line_read);
	shell->tknlist = lexer(line_read);
	//print_lexer(shell->tknlist->head);
	shell->btree = parser(shell);
	//ft_printf("%s\n", shell->btree->left->cmds[0]);
	browse_tree(shell, shell->btree, shell->io_global);
	root_first_search(shell->btree, *display_node);
	dup2(*stdin_cpy, STDIN_FILENO);
	close(*stdin_cpy);
	clear_loop();
}

/*
prompt_loop sert...
la fontion 'signal()' patiente et attent un signal INT, QUIT, ou TSTP
et activera dans ces cas sig_handler.
la fonction dup sert ..
*/

void	prompt_loop(t_shell *shell)
{
	int		stdin_cpy;
	char	*line_read;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTSTP, sig_handler);
	while (1)
	{
		stdin_cpy = dup(STDIN_FILENO);
		shell ->last_gstatus = g_status;
		g_status = 0;
		line_read = readline(create_prompt(shell));
		if (g_status == 130)
		{
			clear_ctrl_c(&stdin_cpy, &line_read);
			continue ;
		}
		if (!line_read)
			builtin_exit(shell, NULL);
		if (line_read && *line_read)
			process_shell(shell, line_read, &stdin_cpy);
		free(line_read);
	}
}
