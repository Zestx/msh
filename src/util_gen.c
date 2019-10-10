/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:00:08 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 19:18:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char **env, char *var_name)
{
	char	*var_content;
	char	**roam;
	size_t	var_len;

	if (!env || !*env || !var_name)
		return (NULL);
	var_len = 0;
	var_len = ft_strlen(var_name);
	roam = env;
	while (*roam)
	{
		if (!ft_strncmp(*roam, var_name, var_len))
		{
			if (!(var_content = ft_strdup(*roam + var_len + 1)))
				exit(EXIT_FAILURE);
			return (var_content);
		}
		roam++;
	}
	return (NULL);
}

char	*cat_path(char *dir, char *name)
{
	char	*full_path;
	int		i;
	int		j;

	if (!(full_path = malloc(ft_strlen(dir) + ft_strlen(name) + 2)))
		exit(EXIT_FAILURE);
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

char	**split_paths(char *paths_var)
{
	char	**paths;

	if (!(paths = ft_strsplit(paths_var, ':')))
		return (NULL);
	return (paths);
}

size_t	count_words(char *str)
{
	size_t	count;
	char	*roam;

	roam = str;
	count = 0;
	while (*roam)
	{
		while (*roam && ft_isspacer(*roam))
			roam++;
		if (*roam && !ft_isspacer(*roam))
		{
			count++;
			while (*roam && !ft_isspacer(*roam))
				roam++;
		}
	}
	return (count);
}

void	realloc_sub(char *str, char ***split, unsigned int i, size_t e)
{
	char *tmp;

	if (!(tmp = ft_strsub(str, i, e - i)))
		exit(EXIT_FAILURE);
	*split = ft_realloc_tab(*split, tmp);
	free(tmp);
}
