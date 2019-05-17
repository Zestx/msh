/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:23:21 by qbackaer          #+#    #+#             */
/*   Updated: 2019/05/17 17:01:48 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	**set_env(char **cmd, char ***envv_l)
{
	if (!cmd[1])
	{
		printenv(*envv_l);
		return (*envv_l);
	}
	if (!cmd[2] || cmd[3])
	{
		ft_putendl("usage: setenv [VAR] [VALUE]");
		return (NULL);
	}
	if (replace_env(cmd, *envv_l) == 1)
		return (*envv_l);
	if (replace_env(cmd, *envv_l) < 0)
		return (NULL);
	if (replace_env(cmd, *envv_l) == 0)
		*envv_l = ft_realloc_tab(*envv_l, set_var(NULL, cmd[1], cmd[2]));
	return (*envv_l);
}

int		replace_env(char **cmd, char **envv_l)
{
	char	**roam;

	roam = envv_l;
	while (*roam)
	{
		if (env_match(cmd[1], *roam))
		{
			if (!(*roam = set_var(*roam, cmd[1], cmd[2])))
				return (-1);
			return (1);
		}
		roam++;
	}
	return (0);
}

int		env_match(char *to_find, char *curr_var)
{
	size_t	len;

	len = ft_strlen(to_find);
	if (!ft_strncmp(to_find, curr_var, len) && curr_var[len] == '=')
		return (1);
	else
		return (0);
}

char	*set_var(char *to_set, char *name, char *value)
{
	char	*new_var;
	int		i;
	int		j;

	if (to_set)
		free(to_set);
	if (!(new_var = malloc(ft_strlen(name) + ft_strlen(value) + 2)))
		return (NULL);
	i = 0;
	while (name[i])
	{
		new_var[i] = name[i];
		i++;
	}
	new_var[i] = '=';
	i++;
	j = 0;
	while (value[j])
	{
		new_var[i] = value[j];
		i++;
		j++;
	}
	new_var[i] = '\0';
	return (new_var);
}