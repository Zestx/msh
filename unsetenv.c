/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 17:07:50 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/07 04:25:48 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static int	is_envv(char *var, char **env)
{
	char **roam;

	roam = env;
	while (*roam)
	{
		if (!ft_strncmp(*roam, var, ft_strlen(var)))
			return (1);
		roam++;
	}
	return (0);
}

static char	**remove_var(char *var, char **env)
{
	char **upd_tab;
	char **roam_n;
	char **roam_o;

	if (!(upd_tab = malloc(sizeof(upd_tab) * get_tab_size(env))))
		exit(EXIT_FAILURE);
	roam_n = upd_tab;
	roam_o = envv_l;
	while (*roam_o)
	{
		if (ft_strncmp(*roam_o, var, ft_strlen(var)))
		{
			*roam_n = ft_strdup(*roam_o);
			roam_n++;
		}
		roam_o++;
	}
	*roam_n = NULL;
	ft_free_tab2(env);
	return (upd_tab);
}

char		**unset_env(char **cmd, char ***env)
{
	char **roam;

	if (!cmd[1])
	{
		ft_putendl("minishell: unsetenv: too few arguments");
		return (*env);
	}
	roam = cmd + 1;
	while (*roam)
	{
		if (is_envv(*roam, *env))
			*env = remove_var(*roam, *env);
		roam++;
	}
	return (*env);
}
