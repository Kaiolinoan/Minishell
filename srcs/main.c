/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/28 17:13:16 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **enviroment)
{
	t_map	*env;
    char    *str;
    char    *path;
	(void)argc;
	(void)argv;
	// (void)enviroment;
	env = new_map();
	create_env(env, enviroment);
    while (1)
    {
        str = readline("minishell> ");
        if (!str) //CTRL + D
        {
            printf("Saindo do minishell!\n");
            free(str);
            env->destroy(env);
            exit(-1);
        }
        if (str && *str)
        {
            int pid = fork();
            if (!pid)
            {
                char **input = ft_split(str, ' ');
                if (!input)
                    return (free(str), env->destroy(env), 0);
                path = get_path(env, str);
                if (!path)
                {
                    // printf("Saindo do minishell!\n");
                    // clear_matriz(input);
                    // free(str);
                    env->destroy(env);
                    exit(-1);
                }
                execve(path, input, enviroment); //lidar com os argumentos dos comandos
                clear_matriz(input);
                free(path);
                printf("falha ao executar execve\n");
            }
            wait(NULL);
        }
        free(str);
        // free(path)
    }
	env->destroy(env);
}
