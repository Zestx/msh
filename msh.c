/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:54:06 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/07 01:32:39 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		dispatch(char **input, char ***envv_l, t_pwd *pwd)
{
	int ret;

	ret = is_builtin(input, envv_l, pwd);
	if (ret < 0)
		return (-1);
	if (ret == 0)
		if (!is_binary(input, envv_l))
		{
			ft_putstr("msh: command not found: ");
			ft_putendl(input[0]);
			return (0);
		}
	return (1);
}

size_t	get_tab_size(char **tab)
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

char	**get_env(char **environ)
{
	char	**envv_l;
	char	**roam;

	if (!(envv_l = malloc(sizeof(environ) * get_tab_size(environ) + 1)))
		exit(EXIT_FAILURE);
	roam = envv_l;
	while (*environ)
	{
		if (!(*roam = ft_strdup(*environ)))
			exit(EXIT_FAILURE);
		environ++;
		roam++;
	}
	roam = NULL;
	return (envv_l);
}

void	msig_handler(int signo)
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

int		main(void)
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
			break ;
		ft_free_tab2(input);
	}
	ft_free_tab2(env);
	ft_free_tab2(input);
	return (0);
}
