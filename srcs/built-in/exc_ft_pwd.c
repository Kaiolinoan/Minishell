/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:24:32 by klino-an          #+#    #+#             */
/*   Updated: 2025/12/26 20:13:05 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_pwd(t_map *env)
{
	char	*buffer;
	char	*env_pwd;

	buffer = getcwd(NULL, 0);
	if (buffer)
	{
		printf("%s\n", buffer);
		free(buffer);
	}
	else
	{
		env_pwd = env->get(env, "PWD");
		if (env_pwd)
			printf("%s\n", env_pwd);
		else
		{
			ft_putstr_fd("pwd: error retrieving current directory: \
				getcwd: cannot access parent directories:", 2);
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			return (1);
		}
	}
	return (0);
}
