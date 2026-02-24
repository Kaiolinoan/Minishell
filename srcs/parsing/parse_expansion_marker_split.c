/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_marker_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 07:05:00 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 06:56:40 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_marker_words(char *str)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\4')
			count++;
		i++;
	}
	return (count);
}

static int	fill_split_string(char *str, char **result)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == '\4')
			i++;
		start = i;
		while (str[i] && str[i] != '\4')
			i++;
		if (i > start)
		{
			result[j] = ft_calloc(i - start + 1, 1);
			if (!result[j])
				return (0);
			ft_strlcpy(result[j], str + start, i - start + 1);
			j++;
		}
	}
	result[j] = NULL;
	return (1);
}

char	**split_on_marker(char *str)
{
	char	**result;
	int		word_count;

	word_count = count_marker_words(str);
	result = ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_split_string(str, result))
		return (clear_matriz2(result), NULL);
	return (result);
}
