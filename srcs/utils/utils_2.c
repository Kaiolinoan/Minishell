/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:47:46 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/14 12:16:32 by klino-an         ###   ########.fr       */
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
