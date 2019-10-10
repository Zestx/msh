/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:33:42 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 18:08:32 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			printenv(char **env)
{
	char	**roam;

	if (!env)
	{
		ft_putendl("minishell: error: empty environement.");
		return ;
	}
	roam = env;
	while (*roam)
	{
		ft_putendl(*roam);
		roam++;
	}
}

static void		prompt_path(void)
{
	char	cwd_buff[PATH_MAX + 1];
	int		i;

	getcwd(cwd_buff, PATH_MAX + 1);
	i = 0;
	while (cwd_buff[i])
	{
		if (cwd_buff[i] != '/')
		{
			ft_putstr(RESET);
			ft_putchar(cwd_buff[i++]);
		}
		else
		{
			ft_putstr(MAG);
			ft_putchar(cwd_buff[i++]);
		}
	}
}

void			prompt(void)
{
	ft_putstr(CYAN);
	ft_putstr("@");
	prompt_path();
	ft_putstr(MAG);
	ft_putstr("➠➤ ");
	ft_putstr(RESET);
}

void			title(void)
{
	ft_putstr("-------------------\n|");
	ft_putstr(MAG);
	ft_putstr("~");
	ft_putstr(RESET);
	ft_putstr(" MiniShell ");
	ft_putstr(CYAN);
	ft_putstr("1.0 ");
	ft_putstr(MAG);
	ft_putstr("~");
	ft_putstr(RESET);
	ft_putstr("|\n-------------------\n");
	ft_putstr("developped by ➠➤ ");
	ft_putstr(CYAN);
	ft_putstr("qbackaer@student.s19.be\n\n\n");
	ft_putstr(RESET);
}
