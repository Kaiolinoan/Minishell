/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:10:17 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/05 14:10:17 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_path(char *old_path, char **commands)
{
	char	*new_path;

	new_path = ft_strjoin(old_path, "/");
	if (!new_path)
		return (NULL);
	new_path = gnl_strjoin(new_path, commands[0]);
	if (!new_path)
		return (free(new_path), NULL);
	return (new_path);
}

char	*get_path(t_map *env, char **commands)
{
	char	**arr_path;
	char	*new_path;
	size_t	i;

	arr_path = ft_split(env->get(env, "PATH"), ':');
	if (!arr_path)
		return (NULL);
	i = 0;
	new_path = NULL;
	while (arr_path[i])
	{
		if (!access(commands[0], F_OK))
			return (clear_matriz(arr_path), commands[0]);
		if (new_path)
			free(new_path);
		new_path = get_full_path(arr_path[i], commands);
		if (!new_path)
			return (clear_matriz(arr_path), NULL);
		if (!access(new_path, F_OK))
			return (clear_matriz(arr_path), new_path);
		i++;
	}
	return (clear_matriz(arr_path), free(new_path), NULL);
}
