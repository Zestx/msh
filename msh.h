/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:55:33 by qbackaer          #+#    #+#             */
/*   Updated: 2019/10/07 01:48:07 by qbackaer         ###   ########.fr       */
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
# include <fcntl.h>
# include <dirent.h>
# include "libft/libft.h"
# include <signal.h>

# define MAG "\x1B[35m"
# define CYAN "\x1B[36m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"

void			title(void);
void			prompt();
size_t			get_tab_size(char **tab);
char			**get_env(char **environ);
char			**get_input(char **envv_l);
int				dispatch(char **input, char ***envv_l);
int				is_builtin(char **cmd, char ***envv_l);
int				is_binary(char **cmd, char ***envv_l);
int				execute(char *path, char **cmd, char **envv_l);
char			*get_env_var(char **envv_l, char *var_name);
char			**split_paths(char *paths_var);
char			**set_env(char **cmd, char ***envv_l);
int				replace_env(char **cmd, char **envv_l);
int				env_match(char *to_find, char *curr_var);
char			*set_var(char *to_set, char *name, char *value);
void			printenv(char **envv_l);
char			**unset_env(char **cmd, char ***envv_l);
void			test_getinp(char **input);
void			test_splits(char **paths);
void			msig_handler(int signo);
void			psig_handler(int signo);
int				cd(char **cmd, char **envv_l);
size_t			count_words(char *str);
char			**init_tab(void);
char			*expand_vars(char *str, char **env);
char			*expand_tilde(char *str, char *home);

#endif
