/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:06:20 by klino-an          #+#    #+#             */
/*   Updated: 2025/10/30 17:21:08 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void built_in_echo(t_command *commands)
{
    // bool new_line;
    printf("bultinnnn\n");
    
    for (size_t j = 0; commands->command[j]; j++)
    {
        printf("[%zu] = %s\n", j,commands->command[j]);
    }
    size_t i  = 1;
    while (commands->command[i])
        printf("%s\n", commands->command[i++]);
}

void built_in_pwd(t_map *env)
{
    printf("%s\n", env->get(env, "PWD"));
}
bool is_built_in(char *str, t_map *env, t_command *commands)
{
    if (!ft_strncmp(str, "env", 3) && ft_strlen(str) == ft_strlen("env"))
    {
        env->print(env);
        return (true);
    }
    if (!ft_strncmp(str, "pwd", 3) && ft_strlen(str) == ft_strlen("pwd"))
    {
        built_in_pwd(env);
        return (true);
    }
    if (!ft_strncmp(str, "echo", 4))
    {
        built_in_echo(commands);
        return (true);
    }

    return (false);
}

void process_input(char *str, t_map *env, char **environment)
{
    int     pid = fork();
    char    *path;

    if (!pid)
    {
        char **input = ft_split(str, ' ');
        if (!input)
        {
            free(str);
            env->destroy(env);
            return ; 
        }
        path = get_path(env, str);
        if (!path)
        {
            printf("aqui tem que ser um command not found!\n");
            clear_matriz(input);
            return ;
        }
        execve(path, input, environment); //lidar com os argumentos dos comandos
        clear_matriz(input);
        free(path);
        printf("falha ao executar execve\n");
    }
    wait(NULL);
}

int	main(int argc, char **argv, char **environment)
{
	t_map	*env;
    char    *str;
    // t_command *commands;

	(void)argc;
	(void)argv;

	env = new_map();
	create_env(env, environment);
    while (1)
    {
        str = readline("minishell> ");
        if (!str) //CTRL + D
        {
            printf("Saindo do minishell!\n");
            free(str);
            break ;
        }
        if (str && *str)
        {
            printf("%s\n",str);
            // commands = new_command(ft_split(str, ' '));
            add_history(str);
            // if (!is_built_in(str, env, commands))
            //     process_input(str, env, environment);
        }
        free(str);
    }
	env->destroy(env);
}
