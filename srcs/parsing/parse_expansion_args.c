/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion_args.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 07:00:00 by kelle             #+#    #+#             */
/*   Updated: 2026/02/24 03:22:41 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_expanded_args(char **args, t_map *env, int i, int j)
{
	int		count;
	char	*expanded;
	char	**split_result;

	count = 0;
	while (args[i])
	{
		expanded = expand(ft_strdup(args[i]), env);
		if (!expanded)
			return (-1);
		split_result = split_on_marker(expanded);
		if (split_result)
		{
			j = 0;
			while (split_result[j++])
				count++;
			clear_matriz2(split_result);
			free(split_result);
		}
		else
			count++;
		free(expanded);
		i++;
	}
	return (count);
}

char	**fill_expanded_args(char **args, char **new_args,
						t_map *env, int i)
{
	int		j;
	int		idx;
	char	*expanded;
	char	**split_result;

	idx = 0;
	while (args[i])
	{
		expanded = expand(args[i], env);
		if (!expanded)
			return (clear_matriz2(new_args), free(new_args), NULL);
		split_result = split_on_marker(expanded);
		if (split_result)
		{
			j = 0;
			while (split_result[j])
				new_args[idx++] = split_result[j++];
			(free(split_result), free(expanded));
		}
		else
			new_args[idx++] = expanded;
		i++;
	}
	new_args[idx] = NULL;
	return (new_args);
}

char	**expand_with_splitting(char **args, t_map *env)
{
	int		total_size;
	char	**new_args;

	total_size = count_expanded_args(args, env, 0, 0);
	if (total_size < 0)
		return (NULL);
	new_args = ft_calloc(total_size + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	return (fill_expanded_args(args, new_args, env, 0));
}
