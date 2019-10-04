/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:39 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/04 20:38:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static char		*get_allvar(char *str, char **env)
{
	char	*start;
	char	**var_list;
	char	**roam;

	//get a tab of all variables names
	start = str;
	while (*start != '$')
		start++;
	start++;
	var_list = ft_strsplit(start, '$');
	//check if all variables are valid
	roam = var_list;
	while (*roam)
	{
		
	}
}

static char		*expand_var(char *str, char **env)
{
	char	*exp;
	size_t	len;

	return (exp);
}

static char		**expand_args(char **args, size_t ac, char **env)
{
	char	**exp;
	char	**e_ptr;
	char	**a_ptr;

	if (!args)
		return (NULL);
	if (!(exp = malloc(sizeof(exp) * (ac + 1))))
		exit(EXIT_FAILURE);
	a_ptr = args;
	e_ptr = exp;
	while (*a_ptr)
	{
		if (ft_strchr(*a_ptr, '$'))
			*e_ptr++ = expand_var(*a_ptr++);
		else if (!(*e_ptr++ = ft_strdup(*a_ptr++)))
			exit(EXIT_FAILURE);
	}
	return (exp);
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
	args = expand_args(args, ac);
	test_getinp(args);
	return (args);
}
