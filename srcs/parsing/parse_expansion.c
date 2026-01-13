/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 15:30:53 by kelle             #+#    #+#             */
/*   Updated: 2026/01/13 00:30:22 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*expand_word(char *str, t_map *env)
// {
// 	char	quote;
// 	char	*new;
// 	int		i;

// 	quote = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		quote = identify_quote(quote, str[i]);
// 		if (quote != '\'' && str[i] == '$' && str[i + 1])
// 		{
// 			new = ;
// 		}
// 		i++;
// 	}
// 	return (new);
// }

// char	*expand(char *str, t_map *env)
// {
// 	char	*new;

// 	if (!str)
// 		return (NULL);
// 	new = expand_word(str, env);
// 	if (!new)
// 		return (NULL);
// 	free(str);
// 	return (new);
// }

// int expand_args(char **args, t_map *env)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i])
// 	{
// 		args[i] = expand(args[i], env);
// 		if (!args[i])
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int		expand_and_shi(t_command *head, t_map *env)
// {
// 	t_command	*current;

// 	current = head;
// 	while (current)
// 	{
// 		if (!expand_args(current->args, env))
// 			return (0);
// 		current = current->next;
// 	}
// 	return (1);
// }
