/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_ft_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:47:21 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/06 16:46:48 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void    only_cd(char *path, t_map *env)
{
    char *home;

    home = env->get(env, "HOME");
    if (home)
    {
        path = home;
        if (chdir(path) == -1)
            perror("cd");
    }
    else
        printf("bash: cd: HOME not set\n");
}
void process_cd(char *path, t_map *env)
{

    if (!path ||  (!ft_strncmp(path, "~", 1) && ft_strlen(path) == 1))
        only_cd(path, env);
    if (!ft_strncmp(path, ".", 1))
        return ;
    else if (!ft_strncmp(path, "..", 2))
    {
        
    }
    else if(!ft_strncmp(path, "-", 1))
    {

    }
    else
    {
        //verificar se tenho um '~' no inicio da str
    }
}

int built_in_cd(char *path, t_map *env)
{
    char *home;

    home = NULL;
    if (!access(path, F_OK))
        return (printf("cd: %s: No such file or directory\n", path));
    if (!access(path, X_OK))
        return (printf("cd: %s: Permission denied\n", path));

    if (commands->command[0] && commands->command[1])
    {
        process_cd(commands->command[1], env);
    }
    return (0);
}
