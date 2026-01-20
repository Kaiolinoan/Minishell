/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 03:01:39 by kelle             #+#    #+#             */
/*   Updated: 2026/01/20 03:49:36 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expanded_string(char *str, int var_pos,
						char *var_name, char *value)
{
	char	*result;
	int		length;
	int		i;
	int		j;

	length = ft_strlen(str) - ft_strlen(var_name) - 1;
	if (value)
		length += ft_strlen(value);
	result = ft_calloc(length + 1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < var_pos)
	{
		result[i] = str[i];
		i++;
	}
	j = 0;
	while (value && value[j])
		result[i++] = value[j++];
	j = var_pos + ft_strlen(var_name) + 1;
	while (str[j])
		result[i++] = str[j++];
	result[i] = '\0';
	return (result);
}

static char	*variable_name(char	*str, int i)
{
	char	*var_name;
	int		var_length;
	int		j;

	var_length = 0;
	while (str[i + var_length] && var_char(str[i + var_length]))
		var_length++;
	var_name = ft_calloc(var_length + 1, 1);
	if (!var_name)
		return (NULL);
	j = 0;
	while (j < var_length)
	{
		var_name[j] = str[i + j];
		j++;
	}
	var_name[var_length] = '\0';
	return (var_name);
}

static char	*expand_variable(char *str, int i, t_map *env)
{
	char	*var_name;
	char	*new;

	if (str[i + 1] == '?')
		return (expanded_string(str, i, "?", env->get(env, "?")));
	if (!var_start(str[i + 1]))
		return (ft_strdup(str));
	var_name = variable_name(str, i + 1);
	if (!var_name)
		return (NULL);
	new = expanded_string(str, i, var_name, env->get(env, var_name));
	free(var_name);
	return (new);
}

static char	*expand_word(char *result, t_map *env, char quote)
{
	char	*new;
	int		i;

	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		quote = identify_quote(quote, result[i]);
		if (quote != '\'' && result[i] == '$' && result[i + 1])
		{
			new = expand_variable(result, i, env);
			if (!new)
				return (free(result), NULL);
			free(result);
			result = new;
			quote = 0;
			i = 0;
			continue ;
		}
		i++;
	}
	new = remove_quotes(result);
	return (free(result), new);
}

char	*expand(char *str, t_map *env)
{
	char	*new;

	if (!str)
		return (NULL);
	new = expand_word(ft_strdup(str), env, 0);
	if (!new)
		return (NULL);
	free(str);
	return (new);
}
