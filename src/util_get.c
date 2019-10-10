/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:57:05 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 19:58:34 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*strdup_safe(char *src)
{
	char *dst;

	if (!(dst = ft_strdup(src)))
		exit(EXIT_FAILURE);
	return (dst);
}

char			*expand_vars_wpr(char *xpnd, char **env)
{
	char *tmp;
	char *expanded;

	tmp = strdup_safe(xpnd);
	free(xpnd);
	expanded = expand_vars(tmp, env);
	free(tmp);
	return (expanded);
}

size_t			get_clean_args(char **args)
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
