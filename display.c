/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:33:42 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/08 18:43:08 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		prompt(void)
{
	char cwd_buff[PATH_MAX + 1];

	ft_putstr("usr");
	ft_putstr(CYAN);
	ft_putstr("@");
	ft_putstr(RESET);
	ft_putstr("computer");
	ft_putstr(MAG);
	ft_putstr(getcwd(cwd_buff, PATH_MAX + 1));
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
