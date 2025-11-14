/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kelle <kelle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:45:33 by kelle             #+#    #+#             */
/*   Updated: 2025/11/14 00:59:14 by kelle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*new_cmdnode(char **args)
{
	t_command	*node;

	node = malloc(sizeof(t_command));
	if (!node)
		return (NULL);
	node->command = args;
	node->infile = NULL;
	node->outfile = NULL;
	node->next = NULL;
	return (node);
}

static t_command	*fill_cmdlist(t_command *head, char *command)
{
	char		**args;
	t_command	*new_node;
	t_command	*current;

	args = ft_split(command, '\2');
	if (!args)
		return (NULL);
	new_node = new_cmdnode(args);
	if (!newnode)
		return (free_grid(args), NULL);
	if (!head)
		head = new_node;
	else
	{
		current = head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	return (head);
}

t_command	*parse_main(char *input, t_command  *head)
{
	size_t	i;
	char	**command;

	input = parse_input(input);
	if (!input)
		return (NULL);
	command = ft_split(input, '\3');
	if (!command)
		return (NULL);
	i = 0;
	while (command[i])
	{
		head = fill_cmdlist(head, command[i]);
		if (!head)
			return (NULL);
		i++;
	}
	free(input);
	free_grid(command);
	return (head);
}
// HEADER
// typedef enum e_type
// {
//     NONE = 0,
//     OUTPUT,
//     OUTPUT_APPEND,
//     INPUT,
//     HEREDOC,
// }   t_type;

// typedef struct	s_redirect
// {
// 	t_type	type;
// 	char *filename;
// 	struct s_redirect *next;
// }	t_redirect;

// // parse utils
// bool						space_only(char *str);

// // utils
// void						free_grid(char **grid);

// MAIN.C
// int	main(int argc, char **argv, char **environment)
// {
// 	char		*str;
// 	t_map		*env;
// 	t_command	*commands;

// 	(void)argc;
// 	(void)argv;
// 	env = new_map();
// 	create_env(env, environment);
// 	while (1)
// 	{
// 		str = readline("minishell> ");
// 		if (!str)
// 		{
// 			printf("Saindo do minishell!\n");
// 			break ;
// 		}
// 		if (*str)
// 			add_history(str);
// 		commands = parse_main(str, commands);
// 		if (!is_built_in(str, env, commands))
// 			process_input(str, env, environment);
// 	}
// 	free (str);
// 	env->destroy(env);
// }

// UTILS.C

// void	free_grid(char **grid)
// {
// 	size_t	i;

// 	i = 0;
// 	while (grid[i])
// 		free(args[i++])
// 	free (args)
// }
