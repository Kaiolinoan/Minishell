/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:17:41 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/14 12:17:41 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_all_num(char *str)
{
	size_t	i;
	bool	sign;

	i = 0;
	sign = false;
	str = ft_strtrim(str, " ");
	if (!str || !*str)
		return (free(str), false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if ((str[0] == '-' || str[0] == '+') && !sign
				&& ft_isdigit(str[1]) != 0)
			{
				sign = true;
				i++;
				continue ;
			}
			return (free(str), false);
		}
		i++;
	}
	return (free(str), true);
}

static int	check_overflow(char *num)
{
	int		sign;
	char	*str;
	size_t	len;

	str = num;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	len = 0;
	while (str[len] >= '0' && str[len] <= '9')
		len++;
	if (len > 19)
		return (0);
	else if (len < 19)
		return (1);
	if (sign == 1)
		return (ft_strncmp(str, "9223372036854775807", 19) <= 0);
	return (ft_strncmp(str, "9223372036854775808", 19) <= 0);
}

static bool	check_exit_arg(char **args, t_map *env,
					t_command *cmd, t_exec *exec)
{
	if (!args)
		return (false);
	if (!args[1])
		return (true);
	if (!is_all_num(args[1]) || !check_overflow(args[1]))
	{
		ft_dprintf(STDERR_FILENO,
			"bash: exit: %s: numeric argument required\n", args[1]);
		ft_exit(env, cmd, exec, 2);
	}
	if (ft_array_len(args) > 2)
		return (ft_dprintf(STDERR_FILENO,
				"bash: exit: too many arguments\n"), false);
	return (true);
}

void	ft_exit(t_map *env, t_command *cmd, t_exec *exec, int nb)
{
	free_all(cmd, exec);
	env->destroy(env);
	exit(nb);
}

int	built_in_exit(t_command *commands, t_map *env, t_exec *exec)
{
	long long			nb;

	nb = 0;
	printf("exit\n");
	if (!commands)
		return (ft_exit(env, commands, exec, 0), 0);
	if (!check_exit_arg(commands->args, env, commands, exec))
		return (1);
	if (commands->args[1])
	{
		nb = ft_atoll(commands->args[1]);
		nb = (unsigned char)nb;
	}
	else
		nb = ft_atoll(env->get(env, "?"));
	close_fds(exec, commands, true);
	ft_exit(env, commands, exec, nb);
	return (nb);
}
