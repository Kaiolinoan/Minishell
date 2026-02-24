/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 07:10:00 by kelle             #+#    #+#             */
/*   Updated: 2026/02/15 06:59:22 by kelle            ###   ########.fr       */
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

static int	copy_value(char *result, int i, char *value)
{
	int	j;

	j = 0;
	while (value && value[j])
	{
		if (value[j] == ' ' || value[j] == '\t')
			result[i++] = '\4';
		else
			result[i++] = value[j];
		j++;
	}
	return (i);
}

static char	*expanded_string_with_splitting(char *str, int var_pos,
						char *var_name, char *value)
{
	char	*result;
	int		length;
	int		i;
	int		j;

	length = ft_strlen(str) - ft_strlen(var_name) - 1;
	if (value)
		length += ft_strlen(value) + (ft_strlen(value) * 1);
	result = ft_calloc(length + 1, 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < var_pos)
	{
		result[i] = str[i];
		i++;
	}
	i = copy_value(result, i, value);
	j = var_pos + ft_strlen(var_name) + 1;
	while (str[j])
		result[i++] = str[j++];
	result[i] = '\0';
	return (result);
}

char	*expand_variable(char *str, int i, t_map *env, char *quote_state)
{
	char	*var_name;
	char	*new;
	char	digit[2];

	if (str[i + 1] == '?')
		return (expanded_string(str, i, "?", env->get(env, "?")));
	if (ft_isdigit(str[i + 1]))
	{
		digit[0] = str[i + 1];
		digit[1] = '\0';
		return (expanded_string(str, i, digit, NULL));
	}
	if (!var_start(str[i + 1]))
		return (str);
	var_name = variable_name(str, i + 1);
	if (!var_name)
		return (NULL);
	if (quote_state && *quote_state == '"')
		new = expanded_string(str, i, var_name, env->get(env, var_name));
	else
		new = expanded_string_with_splitting(str, i,
				var_name, env->get(env, var_name));
	free(var_name);
	return (new);
}
