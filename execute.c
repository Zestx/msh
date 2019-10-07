/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:30:53 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/07 06:27:50 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			is_builtin(char **cmd, char ***env, t_pwd *pwd)
{
	if (!ft_strcmp(cmd[0], "exit"))
		return (-1);
	else if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd, env, pwd);
	else if (!ft_strcmp(cmd[0], "env"))
		printenv(*env);
	else if (!ft_strcmp(cmd[0], "setenv"))
		*env = set_env(cmd, env);
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		*env = unset_env(cmd, env);
	else
		return (0);
	return (1);
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
			closedir(dr);
			return (1);
		}
	closedir(dr);
	return (0);
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

int			is_binary(char **cmd, char ***env)
{
	char	**path_list;
	char	**roam;
	char	*var;
	char	*cat;
	int		found;

	if (!env || !cmd)
		return (0);
	if (cmd[0][0] == '/')
	{
		execute(cmd[0], cmd, *env);
		return (1);
	}
	else if (ft_strchr(cmd[0], '/'))
	{
		var = get_env_var(*env, "HOME");
		cat = cat_path(var, cmd[0]);
		execute(cat, cmd, *env);
		free(var);
		free(cat);
		return (1);
	}
	var = get_env_var(*env, "PATH");
	if (!(path_list = split_paths(var)))
		return (0);
	free(var);
	roam = path_list;
	found = 0;
	while (*roam)
	{
		if (find_binary(*roam, cmd[0]))
		{
			cat = cat_path(*roam, cmd[0]);
			execute(cat, cmd, *env);
			free(cat);
			found = 1;
			break ;
		}
		roam++;
	}
	ft_free_tab2(path_list);
	return (found);
}

int			execute(char *path, char **cmd, char **env)
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
			execve(path, cmd, env);
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
