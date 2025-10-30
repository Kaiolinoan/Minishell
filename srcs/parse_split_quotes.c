/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:33 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/30 18:54:33 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_split
{
	size_t	arr_i;
	size_t	mat_index;
}	t_split;

static size_t	get_word_len(char const *s, char c, size_t *i)
{
	size_t	arr_i;

	arr_i = 0;
	while (s[*i] && s[*i] == c)
		(*i)++;
	while (s[*i] && s[*i] != c)
	{
		if (s[*i] == 39)
		{
			(*i)++;
			while (s[*i] && s[*i] != 39)
			{
				arr_i++;
				(*i)++;
			}
			if (s[*i] == 39)
				(*i)++;
		}
		else
		{
			arr_i++;
			(*i)++;
		}
	}
	return (arr_i);
}

static void	fill_arr(char **str, char const *s, size_t count, size_t i)
{
	t_split	var;

	var.mat_index = 0;
	while (var.mat_index < count)
	{
		var.arr_i = 0;
		while (s[i] && s[i] == ' ')
			i++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] == 39)
			{
				i++;
				while (s[i] && s[i] != 39)
					str[var.mat_index][var.arr_i++] = s[i++];
				if (s[i] == 39)
					i++;
			}
			else
				str[var.mat_index][var.arr_i++] = s[i++];
		}
		str[var.mat_index][var.arr_i] = '\0';
		var.mat_index++;
	}
	str[var.mat_index] = NULL;
}

static size_t	split_str(char **str, char const *s, size_t count, char c)
{
	t_split	var;
	size_t	i;

	i = 0;
	var.mat_index = 0;
	while (var.mat_index < count)
	{
		var.arr_i = get_word_len(s, c, &i);
		str[var.mat_index] = (char *)malloc((var.arr_i + 1) * sizeof(char));
		if (!str[var.mat_index])
			return (free_split(str, var.mat_index), 0);
		var.mat_index++;
	}
	return (1);
}

static size_t	count_words(char const *s, char c, size_t i, size_t count)
{
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if (s[i] == 39)
			{
				count++;
				i++;
				while (s[i] && s[i] != 39)
					i++;
				if (s[i] == 39)
					i++;
			}
			else
			{
				count++;
				while (s[i] && s[i] != c)
					i++;
			}
		}
	}
	return (count);
}

char	**ft_split_quotes(char const *s, char c)
{
	char	**matriz;
	size_t	total_words;

	if (!s)
		return (NULL);
	total_words = count_words(s, c, 0, 0);
	matriz = (char **)malloc((total_words + 1) * sizeof(char *));
	if (!matriz)
		return (NULL);
	if (!split_str(matriz, s, total_words, c))
		return (NULL);
	fill_arr(matriz, s, total_words, 0);
	return (matriz);
}
