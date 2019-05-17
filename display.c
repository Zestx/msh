/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:33:42 by qbackaer          #+#    #+#             */
/*   Updated: 2019/05/17 19:08:03 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*static char	*get_usrname(char **envv_l)
{
	char	*usrname;
	char	**roam;

	if (!envv_l)
		return (NULL);
	roam = envv_l;
	while (*roam)
	{
		if (!ft_strncmp(*roam, "USER=", 5))
		{
			if (!(usrname = ft_strdup(*roam + 5)))
				return (NULL);
			return (usrname);
		}
		roam++;
	}
	return (NULL);
}*/

void		prompt(void)
{
	char cwd_buff[1000];

	ft_putstr("usr");
	ft_putstr(CYAN);
	ft_putstr("@");
	ft_putstr(RESET);
	ft_putstr("computer");
	ft_putstr(MAG);
	ft_putstr(getcwd(cwd_buff, 999));
	ft_putstr(RESET);
	ft_putstr("> ");
}

void		title(void)
{
	ft_putstr("-------------------\n|");
	ft_putstr(MAG);
	ft_putstr("~");
	ft_putstr(RESET);
	ft_putstr(" MINISHELL 0.2 ");
	ft_putstr(MAG);
	ft_putstr("~");
	ft_putstr(RESET);
	ft_putstr("|\n-------------------\n\n");
}
