/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:41:31 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/30 19:58:30 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_tab(char **old_tab, char *new_entry)
{
	int		count;
	char	**new_tab;
	char	**roam;

	if (!old_tab || !new_entry)
		return (NULL);
	count = 0;
	roam = old_tab;
	while (*roam)
	{
		count++;
		roam++;
	}
	if (!(new_tab = malloc(sizeof(new_tab) * (count + 2))))
		return (NULL);
	roam = new_tab;
	while (*old_tab)
	{
		if (!(*roam = ft_strdup(*old_tab)))
			return (NULL);
		old_tab++;
		roam++;
	}
	if (!(*roam = ft_strdup(new_entry)))
			return (NULL);
	new_tab[count + 1] = NULL;
	return (new_tab);
}
