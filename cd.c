/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:30:38 by qbackaer          #+#    #+#             */
/*   Updated: 2019/05/17 21:05:42 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		cd(char **cmd, char **envv_l)
{
	if (cmd [1] && cmd[2])
	{
		ft_putendl("usage: cd <directory>");
		return (1);
	}
	if (!cmd[1] || (cmd[1][0] == '~' && !cmd[1][2]))
		chdir(get_env_var(envv_l, "HOME"));
	else
		if (chdir(cmd[1]))
		{
			if (access(cmd[1], F))
		}
	return (1);
}