/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:30:53 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/26 21:00:46 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	**get_path_list(char **envv_l)
{
	char **roam;
	char **path_list;

	roam = envv_l;
	while (*roam && ft_strncmp(*roam, "PATH=", 5))
		roam++;
	if (!(path_list = ft_strsplit(*roam, ':')))
		return (NULL);
	return (path_list);
}

int		is_builtin(char **cmd, char **envv_l)
{
	envv_l = NULL;
	if (!ft_strcmp(cmd[0], "echo"))
		ft_putendl("builtin command!");
	if (!ft_strcmp(cmd[0], "cd"))
		ft_putendl("builtin command!");
	if (!ft_strcmp(cmd[0], "exit"))
		ft_putendl("builtin command!");
	if (!ft_strcmp(cmd[0], "setenv"))
		ft_putendl("builtin command!");
	if (!ft_strcmp(cmd[0], "unsetenv"))
		ft_putendl("builtin command!");
	if (!ft_strcmp(cmd[0], "env"))
		ft_putendl("builtin command!");
	return (1);
}

int		is_binary(char **cmd, char **envv_l)
{
	char	**path_list;

	if (!(path_list = get_path_list(envv_l)))
		return (0);
	ft_putendl(cmd[0]);
	return (1);
}
