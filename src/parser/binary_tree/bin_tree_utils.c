#include "../../../include/minishell.h"

size_t	count_argc_cmd(t_token *cur)
{
	size_t	argc;

	argc = 0;
	while (cur && is_cmd_tkn(cur->type))
	{
		argc++;
		cur = cur->next;
	}
	return (argc);
}

char	**get_argv_cmd(t_token *cur, size_t argc)
{
	char	**argv;
	size_t	i;

	argv = (char **)gc_calloc(argc + 1, sizeof(char *), B_TREE);
	if (!argv)
		print_and_exit(ERR_MALLOC, RED, 1);
	i = 0;
	while (i < argc)
	{
		cur->used_flag = 1;
		argv[i] = gc_strdup(cur->content, B_TREE);
		if (!argv[i])
			print_and_exit(ERR_MALLOC, RED, 1);
		cur = cur->next;
		i++;
	}
	return (argv);
}

char	**strdup_in_newchar2(char *delimiter)
{
	char	**cpy;

	cpy = (char **)gc_calloc(2, sizeof(char *), B_TREE);
	if (!cpy)
		print_and_exit(ERR_MALLOC, RED, 1);
	cpy[0] = gc_strdup(delimiter, B_TREE);
	if (!cpy[0])
		print_and_exit(ERR_MALLOC, RED, 1);
	return (cpy);
}

char	**extract_cmd_argv(t_token *cur)
{
	size_t	argc;
	char	**argv;

	argc = count_argc_cmd(cur);
	argv = get_argv_cmd(cur, argc);
	if (!argv)
		print_and_exit(ERR_MALLOC, RED, 1);
	return (argv);
}

int	cmd_in_pipe(t_btree *root, int id_branch)
{
	t_btree	*cur;

	cur = root;
	while (cur && cur->branch != id_branch)
	{
		if (cur->type == PIPE)
			return (1);
		if (id_branch < cur->branch)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return (0);
}
