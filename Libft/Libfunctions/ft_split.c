/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:02 by klino-an          #+#    #+#             */
/*   Updated: 2025/04/23 11:04:36 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_mem(char **str, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	fill_arr(char **str, char const *s, size_t count, char c)
{
	size_t	i;
	size_t	arr_i;
	size_t	mat_index;

	i = 0;
	mat_index = 0;
	while (mat_index < count)
	{
		arr_i = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			str[mat_index][arr_i++] = s[i++];
		str[mat_index][arr_i] = '\0';
		mat_index++;
	}
	str[mat_index] = NULL;
}

static int	split_str(char **str, char const *s, size_t count, char c)
{
	size_t	i;
	size_t	arr_i;
	size_t	mat_index;

	i = 0;
	mat_index = 0;
	while (mat_index < count)
	{
		arr_i = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			arr_i++;
			i++;
		}
		str[mat_index] = (char *)malloc((arr_i + 1) * sizeof(char));
		if (!str[mat_index])
		{
			free_mem(str, mat_index);
			return (0);
		}
		mat_index++;
	}
	return (1);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**matriz;
	size_t	total_words;

	if (!s)
		return (NULL);
	total_words = count_words(s, c);
	matriz = (char **)malloc((total_words + 1) * sizeof(char *));
	if (!matriz)
		return (NULL);
	if (!split_str(matriz, s, total_words, c))
		return (NULL);
	fill_arr(matriz, s, total_words, c);
	return (matriz);
}

/* int main()
{
	char str[] = ",,,,,banana,,,,uva,,,,,,maca,,,pera,,,,,";
	char set = ',';
	char **matriz = ft_split(str, set);
	size_t i = 0;
	while (i < count_words(str, set))
	{
		printf("%s\n",matriz[i]);
		free(matriz[i]);
		i++;
	}
	free(matriz);
} */