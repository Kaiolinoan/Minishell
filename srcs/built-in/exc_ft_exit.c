/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:39:55 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/13 10:39:55 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    built_in_exit(t_command *commands, t_map *env, char *str)
{
    size_t i = 0;
    t_command *next;
    while(commands->next)
    {
        next = commands->next;
        i = 0;
        while(commands->command[i])
           free(commands->command[i++]);
        free(commands->command);
        free(commands);
        commands = next;
    }
    env->destroy(env);
    free(str);
    free(commands);
    exit(-1);
}