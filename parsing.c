/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:00:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/29 20:07:42 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*get_env_var(char **envv_l, char *var_name)
{
	char	*var_content;
	char	**roam;
	size_t	var_len;

	if (!envv_l || !*envv_l || !var_name)
		return (NULL);
	var_len = 0;
	var_len = ft_strlen(var_name);
	roam = envv_l;
	while (*roam)
	{
		if (!ft_strncmp(*roam, var_name, var_len))
		{
			var_content = ft_strdup(*roam + var_len + 1);
			return (var_content);
		}
		roam++;
	}
	return (NULL);
}

char	**split_paths(char *paths_var)
{
	char	**paths;

	if (!(paths = ft_strsplit(paths_var, ':')))
		return (NULL);
	return (paths);
}
