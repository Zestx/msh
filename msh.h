/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:55:33 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/26 19:17:35 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"

# define MAG "\x1B[35m"
# define CYAN "\x1B[36m"
# define GREEN "\x1B[32m"
# define RESET "\x1B[0m"

void	title(void);
void	prompt(char **envv_l);
char	*get_username(char	**envv_l);
size_t	get_tab_size(char **tab);
char	**get_env(char **environ);
size_t	count_words(char *str);
char	**fill_avtab(char **av_tab, char *input_str, size_t wc);
char	**get_input(char **envv_l);

#endif
