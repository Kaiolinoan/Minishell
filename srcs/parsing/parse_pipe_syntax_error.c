/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_syntax_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 00:00:00 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 01:27:50 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_spaces_and_check_start(char *input, size_t *i)
{
	*i = 0;
	while (input[*i] == '\2')
		(*i)++;
	if (input[*i] == '\3')
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

static int	check_consecutive_pipes(char *input, size_t *i, int *in_pipe)
{
	if (input[*i] == '\3')
	{
		if (*in_pipe)
		{
			ft_dprintf(2,
				"minishell: syntax error near unexpected token `|'\n");
			return (0);
		}
		*in_pipe = 1;
	}
	else if (input[*i] != '\2')
		*in_pipe = 0;
	return (1);
}

static int	check_trailing_pipe(char *input, size_t i, int in_pipe)
{
	if (in_pipe || (i > 0 && input[i - 1] == '\3'))
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	check_pipe_syntax(char *input)
{
	size_t	i;
	int		in_pipe;

	if (!input || !*input)
		return (1);
	if (!skip_spaces_and_check_start(input, &i))
		return (0);
	in_pipe = 0;
	while (input[i])
	{
		if (!check_consecutive_pipes(input, &i, &in_pipe))
			return (0);
		i++;
	}
	return (check_trailing_pipe(input, i, in_pipe));
}
