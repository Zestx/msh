/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:39 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/06 21:14:39 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char		*glue_arg(char	**split)
{
	char	*arg;
	char 	*tmp;
	char	**roam;

	arg = ft_strdup("");
	roam = split;
	while (*roam)
	{
		tmp = arg;
		arg = ft_strjoin(arg, *roam);
		free(tmp);
		roam++;
	}
	return (arg);
}

static char		**get_val(char **split, char **env)
{
	char	**roam;
	char	*tmp;

	roam = split;
	while (*roam)
	{
		if (*roam[0] == '$')
		{
			free(*roam);
			if (!(tmp = get_env_var(env, (*roam) + 1)))
			{
				if (!(*roam = ft_strdup("")))
					exit(EXIT_FAILURE);
			}
			else if (!(*roam = ft_strdup(tmp)))
				exit(EXIT_FAILURE);
		}
		roam++;
	}
	return (NULL);
}

static char		**lex_var(char *str)
{
	char			**split;
	unsigned int	i;
	size_t			e;

	i = 0;
	e = 0;

	split = init_tab();
	while (str[e] && str[e] != '$')
		e++;
	if (e != i)
		split = ft_realloc_tab(split, ft_strsub(str, i, e - i));
	while (str[i])
	{
		i = ++e;
		while (((str[e] > 64 && str[e] < 91) || (str[e] > 96 && str[e] < 123)) && str[e])
			e++;
		if (str[i - 1] == '$')
			i--;
		split = ft_realloc_tab(split, ft_strsub(str, i, e - i));
		i = e;
		while (str[e] && str[e] != '$')
			e++;
		if (i != e)
			split = ft_realloc_tab(split, ft_strsub(str, i, e - i));
	}
	return (split);
}

static char		*expand_vars(char *str, char **env)
{
	char **split;

	split = lex_var(str);
	get_val(split, env);
	return (glue_arg(split));
}

static char		*expand_tilde(char *str, char *home)
{
	char	*xstr;
	unsigned int	i;
	unsigned int	j;

	if (!(xstr = malloc(ft_strlen(str) + ft_strlen(home))))
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (i == 0 && str[0] == '~' && home[j])
		{
			xstr[j] = home[j];
			j++;
		}
		xstr[i + j] = str[i + 1];
		i++;
	}
	return (xstr);
}

static char		**xpand_args(char **args, char **env, size_t ac)
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
		return (NULL);
	if (!(args = malloc(sizeof(args) * (ac + 1))))
		exit(EXIT_FAILURE);
	args = split_args(args, input_str, ac);
	args = xpand_args(args, env, ac);
	return (args);
}
