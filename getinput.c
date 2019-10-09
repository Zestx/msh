/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:39 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/09 20:38:50 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_clean_args(char **args)
{
	char	**a_ptr;
	size_t	len;

	len = 0;
	a_ptr = args;
	while (*a_ptr)
	{
		if (ft_strcmp(*a_ptr, " ") && ft_strcmp(*a_ptr, ""))
			len++;
		a_ptr++;
	}
	return (len);
}

static char		**clean_args(char **args)
{
	char	**clean;
	char	**args_ptr;
	char	**clean_ptr;

	if (!(clean = malloc(sizeof(clean) * (get_clean_args(args) + 1))))
		exit(EXIT_FAILURE);
	clean[get_clean_args(args)] = NULL;
	args_ptr = args;
	clean_ptr = clean;
	while (*args_ptr)
	{
		if (ft_strcmp(*args_ptr, " ") && ft_strcmp(*args_ptr, ""))
		{
			if (!(*clean_ptr = ft_strdup(*args_ptr)))
				exit(EXIT_FAILURE);
			clean_ptr++;
		}
		args_ptr++;
	}
	ft_free_tab2(args);
	return (clean);
}

static char		**expand_args(char **args, char **env, size_t ac)
{
	char	**xpnd;
	char	*tmp;
	int		i;

	i = 0;
	if (!(xpnd = malloc(sizeof(xpnd) * (ac + 1))))
		exit(EXIT_FAILURE);
	xpnd[ac] = NULL;
	while (args[i])
	{
		if (!(xpnd[i] = ft_strdup(args[i])))
			exit(EXIT_FAILURE);
		if (xpnd[i][0] == '~' && (!xpnd[i][1] || xpnd[i][1] == '/'))
		{
			free(xpnd[i]);
			if (!(tmp = get_env_var(env, "HOME")))
			{
				if (!(xpnd[i] = ft_strdup("")))
					exit(EXIT_FAILURE);
			}
			else if ((xpnd[i] = expand_tilde(args[i], tmp)))
				free(tmp);
		}
		if (ft_strchr(xpnd[i], '$'))
		{
			tmp = ft_strdup(xpnd[i]);
			free(xpnd[i]);
			xpnd[i] = expand_vars(tmp, env);
			free(tmp);
		}
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
	char	**cmds;
	char	*chr;

	prompt(env);
	if (get_next_line(0, &input_str) < 0)
		exit(EXIT_FAILURE);
	if (input_str[0] == ';' || ((chr = ft_strchr(input_str, ';')) && *(chr + 1) == ';'))
	{
		free(input_str);
		ft_putstr("minishell: syntax error: unexpected ';'\n");
		return (NULL);
	}
	if (!(cmds = ft_strsplit(input_str, ';')))
		exit(EXIT_FAILURE);
	free(input_str);
	return (cmds);
}

char			**parse_cmd(char *cmd, char **env)
{
	char **args;
	size_t ac;

	if (!(ac = count_words(cmd)))
	{
		free(cmd);
		return (NULL);
	}
	if (!(args = malloc(sizeof(args) * (ac + 1))))
		exit(EXIT_FAILURE);
	args = split_args(args, cmd, ac);
	free(cmd);
	args = expand_args(args, env, ac);
	args = clean_args(args);
	return (args);
}
