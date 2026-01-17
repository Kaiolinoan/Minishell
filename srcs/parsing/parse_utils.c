/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:25:35 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/16 04:39:11 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	space_only(char *str)
{
	while (*str)
	{
		if (*str != ' ')
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
