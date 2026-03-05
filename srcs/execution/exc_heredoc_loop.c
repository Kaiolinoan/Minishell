/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_heredoc_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 05:10:38 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 05:51:13 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_here_doc(char *line, t_map *env)
{
	char	*expanded;

	expanded = expand_word(ft_strdup(line), env, 0, 0);
	if (!expanded)
	{
		free(line);
		return (NULL);
	}
	free(line);
	return (expanded);
}

void	heredoc_write_line(int fd, char *line,
						bool expand_vars, t_map *env)
{
	char	*expanded;

	if (expand_vars)
	{
		expanded = expand_here_doc(line, env);
		if (!expanded)
			return (free(line));
		ft_dprintf(fd, "%s\n", expanded);
		free(expanded);
	}
	else
	{
		ft_dprintf(fd, "%s\n", line);
		free(line);
	}
}

bool	heredoc_loop(int fd, char *limiter,
	bool expand_vars, t_map *env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_sig == SIGINT)
		{
			free(line);
			open("/tmp/here_temp", O_TRUNC);
			return (false);
		}
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		heredoc_write_line(fd, line, expand_vars, env);
	}
	return (true);
}
