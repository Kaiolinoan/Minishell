/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:47:46 by klino-an          #+#    #+#             */
/*   Updated: 2026/01/16 04:40:11 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clear_matriz2(char **matriz)
{
	size_t	i;

	if (!matriz || !*matriz)
		return ;
	i = 0;
	while (matriz[i])
		free(matriz[i++]);
	matriz = NULL;
}

size_t	ft_array_len(char **arr)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (arr[i])
	{
		count++;
		i++;
	}
	return (count);
}

long long	ft_atoll(const char *str)
{
	long long		nb;
	int				sign;
	size_t			i;

	if (!str)
		return (0);
	nb = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

void	init_exec(t_exec *exec, t_command *cmd)
{
	exec->fds[0] = -1;
	exec->fds[1] = -1;
	exec->in = -1;
	exec->out = -1;
	exec->temp_in = -1;
	exec->temp_out = -1;
	exec->fake_status = -1;
	if (cmd)
		exec->len = list_len_command(cmd);
	else 
		exec->len = 0;
}
