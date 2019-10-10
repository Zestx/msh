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
