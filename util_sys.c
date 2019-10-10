/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_sys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 18:10:17 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 18:11:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		psig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, psig_handler);
	}
}

void		msig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		prompt();
		signal(SIGINT, msig_handler);
	}
}

void		exit_sh(char **env, t_pwd *pwd)
{
	free_pwd(pwd);
	ft_free_tab2(env);
	ft_putchar('\n');
	exit(EXIT_SUCCESS);
}
