/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_syntax_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 06:31:15 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 01:00:27 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_error_token(char redir_type, int remaining)
{
	if (remaining == 1)
	{
		if (redir_type == '<')
			return ("<");
		return (">");
	}
	if (remaining == 2)
	{
		if (redir_type == '<')
			return ("<<");
		return (">>");
	}
	if (redir_type == '<')
		return ("<<<");
	return (">>");
}

int	check_redir_error(t_command *current, int i, char redir_type)
{
	int		len;
	int		max_len;
	int		remaining;
	char	*error_token;

	len = 0;
	while (current->cmd[i][len] == redir_type)
		len++;
	if (redir_type == '<')
		max_len = 3;
	else
		max_len = 2;
	if (len > max_len)
	{
		remaining = len - max_len;
		error_token = get_error_token(redir_type, remaining);
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
			error_token);
		return (0);
	}
	return (1);
}
