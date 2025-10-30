/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:07:35 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/29 16:37:53 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_env(char *env)
{
	static char	*args[2];
	char		*start;
	char		*temp;

	temp = ft_strdup(env);
	if (!temp)
		return (NULL);
	args[1] = NULL;
	start = ft_strchr(temp, '=');
	if (start)
	{
		args[1] = ft_strdup(start + 1);
		*start = '\0';
		args[0] = ft_strdup(temp);
	}
	else
	{
		args[0] = ft_strdup(env);
		args[1] = ft_strdup("");
	}
	return (free(temp), args);
}

void	create_env(t_map *env, char **environment)
{
	size_t	i;
	char	**args;

	i = 0;
	while (environment[i])
	{
		args = ft_split_env(environment[i]);
		if (!args)
			break ;
		if (args[0] && args[1])
			env->put(env, args[0], args[1]);
		else
		{
			if (args[0])
				free(args[0]);
			if (args[1])
				free(args[1]);
		}
		i++;
	}
}

