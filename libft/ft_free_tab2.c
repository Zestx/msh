/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:42:41 by qbackaer          #+#    #+#             */
/*   Updated: 2019/05/09 17:38:01 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_free_tab2(char **tab)
{
	char	**roam;

	if (!tab)
		return ;
	roam = tab;
	while (*roam && **roam)
	{
		free(*roam);
		roam++;
	}
	free(tab);
}
