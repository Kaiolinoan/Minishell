/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:24:45 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/16 02:41:45 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	open_quotes(char *str)
{
	char	quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (str[i])
	{
		quote = identify_quote(quote, str[i]);
		i++;
	}
	return (quote != 0);
}

static void	iso_rightarrow(char *dup, char *str, size_t *i, size_t *j)
{
	if (str[*i] == '>')
	{
		if (*i > 0 && str[*i - 1] == '>')
			dup[(*j)] = '>';
		else if (*i > 0 && str[*i - 1] != ' ')
		{
			dup[*j] = '\2';
			dup[++(*j)] = '>';
		}
		if (str[*i + 1] && str[*i + 1] == '>')
			return ;
		if (str[*i + 1] && str[*i + 1] != ' ')
		{
			dup[*j] = '>';
			dup[++(*j)] = '\2';
		}
	}
}

static void	iso_leftarrow(char *dup, char *str, size_t *i, size_t *j)
{
	if (str[*i] == '<')
	{
		if (*i > 0 && str[*i - 1] == '<')
			dup[(*j)] = '<';
		else if (*i > 0 && str[*i - 1] != ' ')
		{
			dup[*j] = '\2';
			dup[++(*j)] = '<';
		}
		if (str[*i + 1] && str[*i + 1] == '<')
			return ;
		if (str[*i + 1] && str[*i + 1] != ' ')
		{
			dup[*j] = '<';
			dup[++(*j)] = '\2';
		}
	}
}

static void	fill_dup(char *dup, char *str, size_t i, size_t j)
{
	char	flag;

	flag = 0;
	while (str[i])
	{
		flag = identify_quote(flag, str[i]);
		dup[j] = str[i];
		if (!flag)
		{
			if (str[i] == ' ')
				dup[j] = '\2';
			else if (str[i] == '|')
				dup[j] = '\3';
			else if (str[i] == '<')
				iso_leftarrow(dup, str, &i, &j);
			else if (str[i] == '>')
				iso_rightarrow(dup, str, &i, &j);
		}
		i++;
		j++;
	}
}

char	*parse_input(char *str)
{
	char	*dup;

	if (!str || !*str || space_only(str) || open_quotes(str))
		return (NULL);
	dup = ft_calloc(ft_strlen(str), 3);
	if (!dup)
		return (NULL);
	fill_dup(dup, str, 0, 0);
	free (str);
	return (dup);
}
