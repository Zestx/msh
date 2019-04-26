/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:49:39 by qbackaer          #+#    #+#             */
/*   Updated: 2019/04/26 19:16:16 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

size_t	count_words(char *str)
{
	size_t	count;
	char	*roam;

	roam = str;
	count = 0;
	while (*roam)
	{
		while (*roam && ft_isspacer(*roam))
			roam++;
		if (*roam && !ft_isspacer(*roam))
		{
			count++;
			while (*roam && !ft_isspacer(*roam))
				roam++;
		}
	}
	return (count);
}

char	**fill_avtab(char **av_tab, char *input_str, size_t wc)
{
	char	*roam_ptr;
	char	*args_ptr;
	int		word_size;
	size_t	i;

	i = 0;
	roam_ptr = input_str;
	while (*roam_ptr && i < wc)
	{
		while (*roam_ptr && ft_isspacer(*roam_ptr))
			roam_ptr++;
		word_size = 0;
		args_ptr = roam_ptr;
		while (*roam_ptr && !ft_isspacer(*roam_ptr))
		{
			roam_ptr++;
			word_size++;
		}
		if (!(av_tab[i] = strndup(args_ptr, word_size)))
			return (NULL);
		i++;
	}
	av_tab[(int)wc] = NULL;
	return (av_tab);
}

char	**get_input(char **envv_l)
{
	char	*input_str;
	char	**av_tab;

	prompt(envv_l);
	if (get_next_line(0, &input_str) < 0)
		return (NULL);
	if (!(av_tab = malloc(sizeof(av_tab) * (count_words(input_str) + 1))))
		return (NULL);
	if (!(av_tab = fill_avtab(av_tab, input_str, count_words(input_str))))
		return (NULL);
	return (av_tab);
}
