/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:30:53 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/29 20:30:27 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
	return (0);
}

int		is_binary(char **cmd, char **envv_l)
{
	char			**path_list;
	char			**roam;
	int				found;

	if (!envv_l || !cmd)
		return (0);
	if (!(path_list = split_paths(get_env_var(envv_l, "PATH"))))
		return (0);
	roam = path_list;
	found = 0;
	while (*roam)
	{
		if (find_binary(*roam, cmd[0]))
		{
			printf("%s/%s\n", *roam, cmd[0]);
			found = 1;
			break;
		}
		roam++;
	}
	return (found);
}

int		find_binary(char *dirpath, char *binname)
{
	struct dirent	*de;
	DIR				*dr;

	if(!(dr = opendir(dirpath)))
	{
		printf("opendir failure\n");
		return (0);
	}
	while ((de = readdir(dr)))
		if (!ft_strcmp(binname, de->d_name))
		{
			return (1);
			closedir(dr);
		}
	return (0);
	closedir(dr);
}
