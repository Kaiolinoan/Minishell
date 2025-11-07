/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:23:41 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/07 12:34:06 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_unset(t_command *commands, t_map *env)
{
	size_t	i;

	i = 1;
	while (commands->command[i])
		env->remove(env, commands->command[i++]);
}
