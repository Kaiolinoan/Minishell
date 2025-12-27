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

static bool is_all_num(char *str)
{
	size_t i;
	bool sign;

	i = 0;
	sign = false;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if ((str[0] == '-' || str[0] == '+') && !sign
				&& ft_isdigit(str[1]) != 0)
			{
				sign = true;
				i++;
				continue;
			}
			return (false);
		}
		i++;
	}
	return (true);
}
static int check_overflow(char *num)
{
	int	 	sign;
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
        return (strncmp(str, "9223372036854775807", 19) <= 0);
    return (strncmp(str, "9223372036854775808", 19) <= 0);
}

static bool check_exit_arg(char **args, t_map *env, t_command *cmd)
{
	if (!args)
		return (false);
	if (!args[1])
		return (true);
	if (!is_all_num(args[1]) || !check_overflow(args[1]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_exit(env, cmd, 2);
	}
	if (ft_array_len(args) > 2)
		return (ft_putstr_fd("bash: exit: too many arguments\n", 2), false);
	return (true);
}
void ft_exit(t_map *env, t_command *cmd, int nb)
{
	free_all(cmd);
	env->destroy(env);
	exit(nb);
}
int	built_in_exit(t_command *commands, t_map *env)
{
	long long			nb;

	nb = 0;
	printf("exit\n");
	if (!commands)
		return (ft_exit(env, commands, 0), 0);
	if (!check_exit_arg(commands->args, env, commands))
		return (g_exit_code = 1);
	if (commands->args[1])
	{
		nb = ft_atoll(commands->args[1]);
		nb = (unsigned char)nb;
	}
	else
		nb = g_exit_code;
	ft_exit(env, commands, nb);
	return (nb);
}
// falta fazer o bglh do modulo