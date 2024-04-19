#include "../../include/minishell.h"

int	strlen_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	env_sort(char **tab, int len_env)
{
	int		i;
	int		flag;
	char	*tmp;

	flag = 0;
	while (tab && flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < len_env - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				flag = 0;
			}
			i++;
		}
		len_env--;
	}
}

void	print_export(char **tab, t_io fds)
{
	size_t	i;
	size_t	j;
	size_t	size_varname;

	i = 0;
	j = 0;
	while (tab[i])
	{
		size_varname = ft_strlen_until_char(tab[i], '=') + 1;
		j = 0;
		ft_putstr_fd("declare -x", fds.fd_out);
		write(fds.fd_out, tab[i], size_varname);
		write(fds.fd_out, "$\'", 2);
		while (tab[i][size_varname + j])
		{
			if (tab[i][size_varname + j] == 27)
				write (fds.fd_out, "\\", 1);
			write(fds.fd_out, &tab[i][size_varname + j], 1);
			j++;
		}
		write(fds.fd_out, "\'", 1);
		write(fds.fd_out, "\n", 1);
		i++;
	}
}

void	env_print_sorted(t_env *env, t_io fds)
{
	char	**tab;
	char	*str_env;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	free(str_env);
	if (!tab)
		print_and_exit(ERR_MALLOC, RED, 1);
	env_sort(tab, strlen_2d(tab));
	print_export(tab, fds);
	free_2d(tab);
}
