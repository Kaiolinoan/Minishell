/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:23:41 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/26 20:15:00 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_unset(t_command *commands, t_map *env)
{
	size_t	i;

	i = 1;
	while (commands->args[i])
		env->remove(env, commands->args[i++]);
	return (0);
}
