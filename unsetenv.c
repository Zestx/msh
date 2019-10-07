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

static int	is_envv(char *var, char **envv_l)
{
	char **roam;

	roam = envv_l;
	while (*roam)
	{
		if (!ft_strncmp(*roam, var, ft_strlen(var)))
			return (1);
		roam++;
	}
	return (0);
}

static char	**remove_var(char *var, char **envv_l)
{
	char **upd_tab;
	char **roam_n;
	char **roam_o;

	upd_tab = malloc(sizeof(upd_tab) * get_tab_size(envv_l));
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
	ft_free_tab2(envv_l);
	return (upd_tab);
}

char		**unset_env(char **cmd, char ***envv_l)
{
	char **roam;

	if (!cmd[1])
	{
		ft_putendl("too few arguments");
		return (*envv_l);
	}
	roam = cmd + 1;
	while (*roam)
	{
		if (is_envv(*roam, *envv_l))
		{
			if (!(*envv_l = remove_var(*roam, *envv_l)))
				return (NULL);
		}
		roam++;
	}
	return (*envv_l);
}
