/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:35:05 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/07 12:35:05 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print(t_command *commands, size_t i)
{
	printf("%s", commands->command[i]);
	if (commands->command[i + 1])
		printf(" ");
}

static bool	is_valid_flag(char *str)
{
	size_t	j;

	j = 1;
	if (str[0] != '-' || ft_strlen(str) <= 1)
		return (false);
	while (str[j] == 'n')
		j++;
	if (str[j] == '\0')
		return (true);
	return (false);
}

void	built_in_echo(t_command *commands)
{
	size_t	i;
	bool	valid_flag;
	bool	first_flag;

	i = 0;
	valid_flag = false;
	first_flag = true;
	while (commands->command[++i])
	{
		if (first_flag && is_valid_flag(commands->command[i]))
		{
			valid_flag = true;
			if (commands->command[i + 1])
				continue ;
			return ;
		}
		first_flag = false;
		print(commands, i);
	}
	if (!valid_flag)
		printf("\n");
}
