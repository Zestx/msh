/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:54:06 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/26 19:25:04 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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

int		main(void)
{
	extern char **environ;
	char		**envv_l;
	char		**input;

	if (!(envv_l = get_env(environ)))
		return (1);
	title();
	while (1)
		input = get_input(envv_l);
	return (0);
}
