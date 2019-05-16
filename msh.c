/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:54:06 by qbackaer          #+#    #+#             */
/*   Updated: 2019/05/16 20:46:48 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		dispatch(char **input, char ***envv_l)
{
	int ret;

	ret = is_builtin(input, envv_l);
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
	{
		ft_putendl("memory error");
		return (NULL);
	}
	roam = envv_l;
	while (*environ)
	{
		if (!(*roam = ft_strdup(*environ)))
		{
			ft_putendl("memory error");
			return (NULL);
		}
		environ++;
		roam++;
	}
	roam = NULL;
	return (envv_l);
}

static void		sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		prompt();
	}
}

int		main(void)
{
	extern char **environ;
	char		**envv_l;
	char		**input;

	signal(SIGINT, sig_handler);
	if (!(envv_l = get_env(environ)))
		return (1);
	title();
	while (1)
	{
		input = get_input(envv_l);
		if (dispatch(input, &envv_l) < 0)
			break ;
	}
	ft_free_tab2(envv_l);
	ft_free_tab2(input);
	return (0);
}
