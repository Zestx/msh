/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:55:33 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/10 20:34:09 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include "../libft/libft.h"
# include <signal.h>
# include <limits.h>

# define MAG "\x1B[35m"
# define CYAN "\x1B[36m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"

typedef struct	s_pwd
{
	char	*cwd;
	char	*owd;
}				t_pwd;

/*
** minishell.c
*/
char			**get_env(char **environ);
int				dispatch(char **input, char ***env, t_pwd *pwd);

/*
** display.c
*/
void			title(void);
void			prompt();
void			printenv(char **env);

/*
** getinput.c
*/
char			**get_input(char **env, t_pwd *pwd);
char			**parse_cmd(char *cmd, char **env);

/*
** expand.c
*/
char			*expand_vars(char *str, char **env);
char			*expand_tilde(char *str, char *home);

/*
** execute.c
*/
int				is_builtin(char **cmd, char ***env, t_pwd *pwd);
int				is_binary(char **cmd, char ***env);
int				execute(char *path, char **cmd, char **env);

/*
** setenv.c
*/
char			**set_env(char **cmd, char ***env);
int				replace_env(char **cmd, char **env);
int				env_match(char *to_find, char *curr_var);
char			*set_var(char *to_set, char *name, char *value);

/*
** unsetenv.c
*/
char			**unset_env(char **cmd, char ***env);

/*
** cd.c
*/
void			cd(char **cmd, char ***env, t_pwd *pwd);
void			check_access(char *path);

/*
** echo.c
*/
void			echo(char **cmd);

/*
** util_gen.c
*/
char			*get_env_var(char **env, char *var_name);
char			*cat_path(char *dir, char *name);
char			**split_paths(char *paths_var);
size_t			count_words(char *str);
void			realloc_sub(char *str, char ***split, unsigned int i, size_t e);

/*
** util_get.c
*/
char			*strdup_safe(char *src);
char			*expand_vars_wpr(char *xpnd, char **env);
size_t			get_clean_args(char **args);
void			rm_quotes(char **args);

/*
** util_tab.c
*/
char			**init_tab(void);
size_t			get_tab_size(char **tab);

/*
** util_pwd.c
*/
int				update_pwd(char ***env, char *var, char *value);
void			update_s_pwd(t_pwd *pwd);
int				init_pwd(t_pwd *pwd);
void			free_pwd(t_pwd *pwd);

/*
** util_sys.c
*/
void			msig_handler(int signo);
void			psig_handler(int signo);
void			exit_sh(char **env, t_pwd *pwd);
int				access_error_wpr(char *path, int type, struct stat st);

#endif
