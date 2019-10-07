/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:30:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/07 04:33:30 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	dir_access(char *path)
{
	struct stat st;

	ft_putstr("minishell: cd: ");
	ft_putstr(path);
	if (access(path, F_OK))
		ft_putstr("no such file or directory\n");
	else if (access(path, R_OK))
		ft_putstr("permission denied\n");
	else if (!lstat(path, &st) && !S_ISDIR(st.st_mode))
		ft_putstr("not a directory\n");
	else
		ft_putstr("unidentified error\n");
}

static void	chdir_home(char ***env)
{
	char	*home;
	char	**roam;

	if (!(home = get_env_var(*env, "HOME")))
		ft_putstr("minishell: cd: HOME not set\n");
	else if (chdir(home))
		dir_access(home);
	else
	{
	}
}

static void	chdir_oldpwd(char ***env)
{
	char *oldpwd;

	if (!(oldpwd = get_env_var(*env, "OLDPWD")))
		ft_putstr("minishell: cd: OLDPWD not set\n");
	else if (chdir(oldpwd))
		dir_access(oldpwd);
	else
	{
	}
}

static void	chdir_arg(char *path)
{
	if (chdir(path))
		dir_access(path);
	else
	{
	}
}

void		cd(char **cmd, char **env)
{
	if (!cmd[1] || !ft_strcmp(cmd[1], "--"))
		chdir_home(&env);
	else if (!ft_strcmp(cmd[1], "-"))
		chdir_oldpwd(&env);
	else
		chdir_arg(cmd[1]);
}

