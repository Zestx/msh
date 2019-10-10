/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:55:33 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/08 17:38:54 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include "libft/libft.h"
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
}		t_pwd;

void			title(void);
void			prompt();
void			nl_prompt();
size_t			get_tab_size(char **tab);
char			**get_env(char **environ);
char			**get_input(char **env, t_pwd *pwd);
char			**parse_cmd(char *cmd, char **env);
int			dispatch(char **input, char ***env, t_pwd *pwd);
int			is_builtin(char **cmd, char ***env, t_pwd *pwd);
int			is_binary(char **cmd, char ***env);
int			execute(char *path, char **cmd, char **env);
char			*get_env_var(char **env, char *var_name);
char			**split_paths(char *paths_var);
char			**set_env(char **cmd, char ***env);
int			replace_env(char **cmd, char **env);
int			env_match(char *to_find, char *curr_var);
char			*set_var(char *to_set, char *name, char *value);
void			printenv(char **env);
char			**unset_env(char **cmd, char ***env);
void			test_getinp(char **input);
void			test_splits(char **paths);
void			msig_handler(int signo);
void			psig_handler(int signo);
void			cd(char **cmd, char ***env, t_pwd *pwd);
size_t			count_words(char *str);
char			**init_tab(void);
char			*expand_vars(char *str, char **env);
char			*expand_tilde(char *str, char *home);
int			update_pwd(char ***env, char *var, char *value);
void			echo(char **cmd);
void			update_s_pwd(t_pwd *pwd);
int			init_pwd(t_pwd *pwd);
void			free_pwd(t_pwd *pwd);
void			exit_sh(char **env, t_pwd *pwd);

#endif
