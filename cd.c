/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:30:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/07 06:16:30 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	dir_access(char *path)
{
	struct stat st;

	ft_putstr("minishell: cd: ");
	ft_putstr(path);
	if (access(path, F_OK))
		ft_putstr(": no such file or directory\n");
	else if (access(path, R_OK))
		ft_putstr(": permission denied\n");
	else if (!lstat(path, &st) && !S_ISDIR(st.st_mode))
		ft_putstr(": not a directory\n");
	else
		ft_putstr(": unidentified error\n");
}

static void	chdir_home(char ***env, t_pwd *pwd)
{
	char	*home;
	char	*tmp;

	if (!(home = get_env_var(*env, "HOME")))
		ft_putstr("minishell: cd: HOME not set\n");
	else if (chdir(home))
		dir_access(home);
	else
	{
		if ((tmp = get_env_var(*env, "PWD")))
		{
			update_pwd(env, "OLDPWD", tmp);
			free(tmp);
		}
		update_pwd(env, "PWD", home);
		update_s_pwd(pwd);
	}
	if (home)
		free(home);
}

static void	chdir_oldpwd(char ***env, t_pwd *pwd)
{
	char	*tmp;

	if (chdir(pwd->owd))
		dir_access(pwd->owd);
	else
	{
		if ((tmp = get_env_var(*env, "PWD")))
		{
			update_pwd(env, "OLDPWD", tmp);
			free(tmp);
		}
		update_pwd(env, "PWD", pwd->owd);
		update_s_pwd(pwd);
	}
}

static void	chdir_arg(char *path, char ***env, t_pwd *pwd)
{
	char	*tmp;

	if (chdir(path))
		dir_access(path);
	else
	{
		if ((tmp = get_env_var(*env, "PWD")))
		{
			update_pwd(env, "OLDPWD", tmp);
			free(tmp);
		}
		update_pwd(env, "PWD", path);
		update_s_pwd(pwd);
	}
}

void		cd(char **cmd, char ***env, t_pwd *pwd)
{
	if (!cmd[1] || !ft_strcmp(cmd[1], "--"))
		chdir_home(env, pwd);
	else if (!ft_strcmp(cmd[1], "-"))
		chdir_oldpwd(env, pwd);
	else
		chdir_arg(cmd[1], env, pwd);
}
