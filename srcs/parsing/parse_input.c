/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:18:00 by kemontei          #+#    #+#             */
/*   Updated: 2025/11/07 12:45:53 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	open_quotes(char *str)
{
	char	flag;
	size_t	i;

	flag = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !flag)
			flag = str[i];
		else if (flag == str[i])
			flag = 0;
		i++;
	}
	return (flag != 0);
}

static void	iso_rightarrow(char *dup, char *str, size_t *i, size_t *j)
{
	if (str[*i] == '>')
	{
		if (str[*i - 1] && str[*i - 1] == '>')
			dup[(*j)] = '>';
		else if (str[*i - 1] && str[*i - 1] != ' ')
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
		if (str[*i - 1] && str[*i - 1] == '<')
			dup[(*j)] = '<';
		else if (str[*i - 1] && str[*i - 1] != ' ')
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
		if (!flag && (str[i] == '\'' || str[i] == '"'))
			flag = str[i];
		else if (flag == str[i])
			flag = 0;
		dup[j] = str[i];
		if (flag == 0)
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
		return (ft_printf("boo"), NULL);
	dup = ft_calloc(ft_strlen(str), 3);
	if (!dup)
		return (NULL);
	fill_dup(dup, str, 0, 0);
	return (dup);
}
