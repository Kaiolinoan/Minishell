/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:47:46 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/02 16:29:21 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str, char *filename)
{
	write(2, str, ft_strlen(str));
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 2);
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

void	free_grid(char **grid)
{
	size_t	i;

	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

void list_clear_redir(t_redirect *head)
{
	t_redirect *next;

	if (!head)
		return ;
	while(head)
	{
		next = head->next;
		ft_close(&head->fd);
		free(head);
		head = next;
	}
	head = NULL;
}
