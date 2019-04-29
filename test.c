/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:08:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/29 19:25:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	test_getenv(char **envv_l)
{
	char	**roam;

	if (!envv_l)
	{
		ft_putendl("test_getenv: error.");
		return ;
	}
	ft_putendl("ENVIRONEMENT VARIABLES");
	ft_putendl("======================");
	roam = envv_l;
	while (*roam)
	{
		ft_putendl(*roam);
		roam++;
	}
	ft_putendl("======================");
}

void	test_getinp(char **input)
{
	char	**roam;
	int		i;

	if (!input)
	{
		ft_putendl("test_getinp: error.");
		return ;
	}
	ft_putendl("USER INPUT:");
	ft_putendl("======================");
	roam = input;
	i = 0;
	while (*roam)
	{
		printf("arg[%d]: %s\n", i, *roam);
		roam++;
		i++;
	}
	ft_putendl("======================");
}

void	test_splits(char **paths)
{
	char	**roam;
	int		i;

	if (!paths)
	{
		ft_putendl("test_splits: error.");
		return ;
	}
	ft_putendl("BINARY LOCATIONS:");
	ft_putendl("======================");
	roam = paths;
	i = 0;
	while (*roam)
	{
		printf("path[%d]: %s\n", i, *roam);
		roam++;
		i++;
	}
	ft_putendl("======================");
}
