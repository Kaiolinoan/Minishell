/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klino-an <klino-an@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:26:27 by klino-an          #+#    #+#             */
/*   Updated: 2025/11/21 19:54:40 by klino-an         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_built_in(t_map *env, t_command *commands)
{
	char *str;

	str = commands->command[0];
	if (!ft_strcmp(str, "env"))
		return (env->print(env), true);
	if (!ft_strcmp(str, "pwd"))
		return (built_in_pwd(env), true);
	if (!ft_strcmp(str, "echo"))
		return (built_in_echo(commands), true);
	if (!ft_strcmp(str, "unset"))
		return (built_in_unset(commands, env), true);
	if (!ft_strcmp(str, "export"))
		return (built_in_export(commands, env), true);
	if (!ft_strcmp(str, "cd"))
		return (built_in_cd(commands->command, env), true);
	if (!ft_strcmp(str, "exit"))
		return (built_in_exit(commands, env), true);
	return (false);
}

static void	single_command(t_map *env, t_command *commands, t_pipe *pipe)
{
	int		pid;
	char	*path;

	pid = fork();
	if (pid < 0)
		printf("erro no fork\n");
	else if (pid == 0)
	{
		check_redir(commands->infile, commands->outfile, pipe);
		path = get_path(env, commands->command);
		if (!path)
		{
			printf("aqui tem que ser um command not found!\n");
			return ;
		}
		execve(path, commands->command, env->to_string(env));
		free(path);
		printf("falha ao executar execve\n");
	}
	else
		wait(NULL);
}

static void	child_process(t_map *env, t_command *commands, t_pipe *pipe)
{
	char *path;
	
	path = get_path(env, commands->command);
	if (!path)
	{
		for (int i = 0; commands->command[i]; i++)
			printf("%s\n", commands->command[i]);
		printf("aqui tem que ser um command not found!\n");
		exit (127);
	}
	if (pipe->prev && !commands->infile)
		dup2(pipe->prev[0], STDIN_FILENO);
	if (commands->next && !commands->outfile) 
		dup2(pipe->current[1], STDOUT_FILENO);
	close_all(pipe);
	if (is_built_in(env, commands))
		exit(g_exit_code);
	execve(path, commands->command, env->to_string(env));
	ft_printf("erro no execve");
	exit (127);
}

void test_out(t_command *commands)
{
	t_redirect *out;

	out = malloc(sizeof(t_redirect));
	if (!out)
		return ;
	out->filename = "b";
	out->type = OUTPUT;
	commands->outfile = out;
}

void test_in(t_command *commands)
{
	t_redirect *in;

	in = malloc(sizeof(t_redirect));
	if (!in)
		return ;
	in->filename = "a";
	in->type = INPUT;
	commands->infile = in;
}

void	handle_input (char *str, t_map *env)
{
	t_command	*commands;
	t_pipe		*pipe;
	pid_t		pid;

	pipe = malloc (sizeof(t_pipe));
	if (!pipe)
		return ;
	commands = NULL;
	commands = parse_main(str, commands);
	// printf("BEFORE TEST OUTFILE PTR: %p\n", commands->outfile);
	test_in(commands);
	commands->outfile = NULL;

	// printf("AFTER TEST OUTFILE PTR: %p\n", commands->outfile);
	if (!commands->next)
	{
		if (!is_built_in(env, commands))
			return (single_command(env, commands, pipe));
		else 
			exit (2);
	}
	printf("klasdlaskdlasdklsadkdaslksda\n");
	initialize_pipes(pipe);
	while (commands)
	{
		if (commands->next)
			if (!create_pipes(pipe))
				return ((void)printf("ERROR: pipe()\n"));
		pid = fork();
		if (pid < 0)
			return ((void)printf("erro no fork\n"));
		else if (pid == 0)
			child_process(env, commands, pipe);
		else
		{
		    if (commands->next)
		        ft_close(&pipe->current[1]);
		    if (pipe->prev)
		        (ft_close(&pipe->prev[0]), ft_close(&pipe->prev[1]));
		}
		switch_pipes(pipe);
		commands = commands->next;
	}
	while (wait(NULL) != -1);
	free(pipe);
}