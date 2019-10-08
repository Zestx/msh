/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:54:06 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/08 20:12:14 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			dispatch(char **input, char ***env, t_pwd *pwd)
{
	int ret;

	ret = is_builtin(input, env, pwd);
	if (ret < 0)
		return (-1);
	if (ret == 0)
	{
		ret = is_binary(input, env);
		if (ret == 0)
		{
			if (ft_strcmp(input[0], ""))
			{
				ft_putstr("msh: ");
				ft_putstr(input[0]);
				ft_putstr(": command not found.\n");
			}
			return (0);
		}
		if (ret == -1)
			return (0);
	}
	return (1);
}

size_t		get_tab_size(char **tab)
{
	size_t	size;
	char	**roam;

	if (!tab)
		return (0);
	roam = tab;
	size = 0;
	while (*roam)
	{
		size++;
		roam++;
	}
	return (size);
}

char		**get_env(char **environ)
{
	char	**copy;
	char	**env_ptr;
	char	**cpy_ptr;

	if (!(copy = malloc(sizeof(copy) * (get_tab_size(environ) + 1))))
		exit(EXIT_FAILURE);
	env_ptr = environ;
	cpy_ptr = copy;
	while (*env_ptr)
	{
		if (!(*cpy_ptr = ft_strdup(*env_ptr)))
			exit(EXIT_FAILURE);
		cpy_ptr++;
		env_ptr++;
	}
	*cpy_ptr = NULL;
	return (copy);
}

void		msig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		prompt();
	}
}

static int	init_pwd(t_pwd *pwd)
{
	char tmp[PATH_MAX + 1];

	if (!(getcwd(tmp, PATH_MAX + 1)))
		return (0);
	if (!(pwd->cwd = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	if (!(pwd->owd = ft_strdup(tmp)))
		exit(EXIT_FAILURE);
	return (1);
}

static void	free_pwd(t_pwd *pwd)
{
	free(pwd->cwd);
	free(pwd->owd);
}

int			main(void)
{
	extern char **environ;
	char		**env;
	char		**input;
	t_pwd		pwd;

	if (!init_pwd(&pwd))
		exit(EXIT_FAILURE);
	signal(SIGINT, msig_handler);
	if (!(env = get_env(environ)))
		return (1);
	title();
	while (1)
	{
		input = get_input(env);
		if (!input || !input[0])
		{
			ft_free_tab2(input);
			continue ;
		}
		if (dispatch(input, &env, &pwd) < 0)
		{
			ft_free_tab2(input);
			break ;
		}
		ft_free_tab2(input);
	}
	free_pwd(&pwd);
	ft_free_tab2(env);
	return (0);
}
