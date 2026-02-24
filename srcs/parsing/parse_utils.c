/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:25:35 by klino-an          #+#    #+#             */
/*   Updated: 2026/02/24 02:58:48 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	space_only(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (false);
		str++;
	}
	return (true);
}

char	identify_quote(char flag, char c)
{
	if (!flag && (c == '"' || c == '\''))
		return (c);
	if (flag && flag == c)
		return (0);
	return (flag);
}

bool	var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*remove_quotes(char *str)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	result = ft_calloc(ft_strlen(str) + 1, 1);
	if (!result)
		return (NULL);
	quote = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (quote && quote == str[i])
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
