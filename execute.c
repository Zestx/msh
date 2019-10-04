/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:30:53 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/04 19:41:47 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			is_builtin(char **cmd, char ***envv_l)
{
	if (!ft_strcmp(cmd[0], "echo"))
		ft_putendl("builtin command!");
	if (!ft_strcmp(cmd[0], "cd"))
	{
		cd(cmd, *envv_l);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "exit"))
		return (-1);
	if (!ft_strcmp(cmd[0], "setenv"))
	{
		if (!(*envv_l = set_env(cmd, envv_l)))
			return (0);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "unsetenv"))
	{
		if (!(*envv_l = unset_env(cmd, envv_l)))
			return (0);
		return (1);
	}
	if (!ft_strcmp(cmd[0], "env"))
		printenv(*envv_l);
	return (0);
}

static int	find_binary(char *dirpath, char *binname)
{
	struct dirent	*de;
	DIR				*dr;

	if (!(dr = opendir(dirpath)))
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

static char	*cat_path(char *dir, char *name)
{
	char	*full_path;
	int		i;
	int		j;

	if (!(full_path = malloc(ft_strlen(dir) + ft_strlen(name) + 2)))
		return (NULL);
	i = 0;
	while (dir[i])
	{
		full_path[i] = dir[i];
		i++;
	}
	full_path[i++] = '/';
	j = 0;
	while (name[j])
	{
		full_path[i] = name[j];
		j++;
		i++;
	}	
	full_path[i] = '\0';
	return (full_path);
}

int			is_binary(char **cmd, char ***envv_l)
{
	char	**path_list;
	char	**roam;
	int		found;

	if (!envv_l || !cmd)
		return (0);
	if (cmd[0][0] == '/')
	{
		execute(cmd[0], cmd, *envv_l);
		return (1);
	}
	else if (ft_strchr(cmd[0], '/'))
	{
		execute(cat_path(get_env_var(*envv_l, "HOME"), cmd[0]), cmd, *envv_l);
		return (1);
	}
	if (!(path_list = split_paths(get_env_var(*envv_l, "PATH"))))
		return (0);
	roam = path_list;
	found = 0;
	while (*roam)
	{
		if (find_binary(*roam, cmd[0]))
		{
			execute(cat_path(*roam, cmd[0]), cmd, *envv_l);
			found = 1;
			break ;
		}
		roam++;
	}
	return (found);
}

int			execute(char *path, char **cmd, char **envv_l)
{
	pid_t		pid;
	struct stat	st_buff;

	if (!path)
		return (0);
	lstat(path, &st_buff);
	if (S_ISREG(st_buff.st_mode) && st_buff.st_mode & S_IXUSR)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(path, cmd, envv_l);
			exit(EXIT_SUCCESS);
		}
		if (pid > 0)
			wait(&pid);
		if (pid < 0)
		{
			ft_putendl("forking failed.");
			return (0);
		}
	}
	else
		return (0);
	return (1);
}
