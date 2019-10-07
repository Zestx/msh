/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:39 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/07 01:48:34 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char		**expand_args(char **args, char **env, size_t ac)
{
	char	**xpnd;
	int		i;

	if (!(xpnd = malloc(sizeof(xpnd) * (ac + 1))))
		exit(EXIT_FAILURE);
	xpnd[ac] = NULL;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '~' && (!args[i][1] || args[i][1] == '/'))
			xpnd[i] = expand_tilde(args[i], get_env_var(env, "HOME"));
		else if (ft_strchr(args[i], '$'))
			xpnd[i] = expand_vars(args[i], env);
		else if (!(xpnd[i] = ft_strdup(args[i])))
			exit(EXIT_FAILURE);
		i++;
	}
	ft_free_tab2(args);
	return (xpnd);
}

static char		**split_args(char **args, char *input_str, size_t ac)
{
	char	*roam;
	char	*start;
	int		arg_len;
	size_t	i;

	i = 0;
	roam = input_str;
	while (*roam && i < ac)
	{
		while (*roam && ft_isspacer(*roam))
			roam++;
		arg_len = 0;
		start = roam;
		while (*roam && !ft_isspacer(*roam++))
			arg_len++;
		if (!(args[i] = strndup(start, arg_len)))
			exit(EXIT_FAILURE);
		i++;
	}
	args[(int)ac] = NULL;
	return (args);
}

char			**get_input(char **env)
{
	char	*input_str;
	char	**args;
	size_t	ac;

	prompt(env);
	if (get_next_line(0, &input_str) < 0)
		exit(EXIT_FAILURE);
	if (!(ac = count_words(input_str)))
	{
		free(input_str);
		return (NULL);
	}
	if (!(args = malloc(sizeof(args) * (ac + 1))))
		exit(EXIT_FAILURE);
	args = split_args(args, input_str, ac);
	free(input_str);
	args = expand_args(args, env, ac);
	return (args);
}
