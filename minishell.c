/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:54:06 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 18:09:35 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			dispatch(char **input, char ***env, t_pwd *pwd)
{
	int ret;

	ret = is_builtin(input, env, pwd);
	if (ret < 0)
		return (-1);
	if (ret == 0)
	{
		ret = is_binary(input, env);
		if (ret == 0)
		{
			if (ft_strcmp(input[0], ""))
			{
				ft_putstr("msh: ");
				ft_putstr(input[0]);
				ft_putstr(": command not found.\n");
			}
			return (0);
		}
		if (ret == -1)
			return (0);
	}
	return (1);
}

char		**get_env(char **environ)
{
	char	**copy;
	char	**env_ptr;
	char	**cpy_ptr;

	if (!(copy = malloc(sizeof(copy) * (get_tab_size(environ) + 1))))
		exit(EXIT_FAILURE);
	env_ptr = environ;
	cpy_ptr = copy;
	while (*env_ptr)
	{
		if (!(*cpy_ptr = ft_strdup(*env_ptr)))
			exit(EXIT_FAILURE);
		cpy_ptr++;
		env_ptr++;
	}
	*cpy_ptr = NULL;
	return (copy);
}

void 	test(char **ptr, int *exit, char ***env, t_pwd *pwd)
{
	char	**cmd;

	cmd = NULL;
	while (*ptr)
	{
		cmd = parse_cmd(*ptr, *env);
		if (!cmd || !cmd[0])
		{
			ft_free_tab2(cmd);
			break ;
		}
		if (dispatch(cmd, env, pwd) < 0)
		{
			*exit = 1;
			ft_free_tab2(cmd);
			break ;
		}
		ft_free_tab2(cmd);
		ptr++;
	}
}

static void	prompt_loop(char ***env, t_pwd *pwd)
{
	char	**ptr;
	char	**all_cmds;
	int		exit;

	exit = 0;
	while (1)
	{
		if (!(all_cmds = get_input(*env, pwd)))
			continue;
		ptr = all_cmds;
		test(ptr, &exit, env, pwd);
		free(all_cmds);
		if (exit)
			break ;
	}
}

int			main(void)
{
	extern char **environ;
	char		**env;
	t_pwd		pwd;

	if (!init_pwd(&pwd))
		exit(EXIT_FAILURE);
	signal(SIGINT, msig_handler);
	if (!(env = get_env(environ)))
		return (1);
	title();
	prompt_loop(&env, &pwd);
	free_pwd(&pwd);
	ft_free_tab2(env);
	return (0);
}
