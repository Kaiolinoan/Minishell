/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 03:01:39 by kelle             #+#    #+#             */
/*   Updated: 2026/03/04 01:25:13 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_word(char *result, t_map *env, char quote, int i)
{
	char	*new;

	if (!result)
		return (NULL);
	while (result[i])
	{
		quote = identify_quote(quote, result[i]);
		if (quote != '\'' && result[i] == '$' && result[i + 1])
		{
			new = expand_variable(result, i, env, &quote);
			if (!new)
				return (free(result), NULL);
			if (new != result)
			{
				free(result);
				result = new;
				quote = 0;
				i = 0;
				continue ;
			}
		}
		i++;
	}
	new = remove_quotes(result, 0);
	return (free(result), new);
}

char	*expand(char *str, t_map *env)
{
	char	*new;

	if (!str)
		return (NULL);
	new = expand_word(ft_strdup(str), env, 0, 0);
	if (!new)
		return (free(str), NULL);
	free(str);
	return (new);
}
