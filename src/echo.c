/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 06:18:47 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/08 18:46:42 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_nopt(char *str)
{
	char	*ptr;

	ptr = str;
	if (*ptr != '-')
		return (0);
	ptr++;
	while (*ptr)
	{
		if (*ptr != 'n')
			return (0);
		ptr++;
	}
	return (1);
}

void		echo(char **cmd)
{
	char	**roam;
	int		n;
	int		a;
	int		f;

	n = 0;
	a = 0;
	f = 0;
	if (*(cmd + 1) && (roam = cmd + 1))
		while (*roam)
		{
			if (is_nopt(*roam) && !a)
				n = 1;
			else
			{
				if (f)
					ft_putchar(' ');
				ft_putstr(*roam);
				a = 1;
				f = 1;
			}
			roam++;
		}
	if (!n)
		ft_putchar('\n');
}
