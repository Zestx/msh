/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:41:31 by qbackaer          #+#    #+#             */
/*   Updated: 2019/05/03 14:54:15 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_realloc_tab(char **old_tab, char *new_entry)
{
	int		count;
	char	**new_tab;
	char	**roam_o;
	char	**roam_n;

	if (!old_tab || !new_entry)
		return (NULL);
	count = 0;
	roam_o = old_tab;
	while (*roam_o)
	{
		count++;
		roam_o++;
	}
	if (!(new_tab = malloc(sizeof(new_tab) * (count + 2))))
		return (NULL);
	roam_n = new_tab;
	roam_o = old_tab;
	while (*roam_o)
	{
		if (!(*roam_n = ft_strdup(*roam_o)))
			return (NULL);
		roam_o++;
		roam_n++;
	}
	if (!(*roam_n = ft_strdup(new_entry)))
			return (NULL);
	new_tab[count + 1] = NULL;
	ft_free_tab2(old_tab);
	return (new_tab);
}
