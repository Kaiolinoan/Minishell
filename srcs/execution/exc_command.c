#include "minishell.h"

static int check_error_msg(t_command *cmd)
{
	if (!cmd->path[0])
		return (ft_putstr_fd(*cmd->args, 2), ft_putstr_fd(": command not found\n", 2), 127);
	else if (errno == ENOENT)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	else if (errno ==  EACCES)
	{
		DIR *d;

		d = opendir(cmd->args[0]);
		if (d)
		{
			(closedir(d), ft_putstr_fd(cmd->args[0], 2));
			return (ft_putstr_fd(": Is a directory\n", 2), 126);
		}
		else 
		{
			ft_putstr_fd(cmd->args[0], 2);
			return (ft_putstr_fd(": Permission denied\n", 2), 126);
		}
	}
	return (127);
}

void exec_failure(t_map *env, t_command *cmd, int *in, int *out)
{
	int exit_code;

	exit_code = check_error_msg(cmd);
	ft_close(in);
	ft_close(out);
	ft_exit(env, cmd, exit_code);
}

void close_fds(t_exec *exec) //checar isso depois
{
	ft_close(&exec->in);
	ft_close(&exec->out);
    ft_close(&exec->fds[0]);
    ft_close(&exec->fds[1]);
	// ft_close(&cmd->infile->fd);
}
static int single_built_in(t_command *cmd, t_map *env)
{
	int 	built_in_status;

	built_in_status = is_built_in(env, cmd);
	if (built_in_status != -1)
		env->put(env, ft_strdup("?"), ft_itoa(built_in_status), true); //alterar para false dps que tiver a expansao
	return (built_in_status);
}
void execute_command(t_command *cmd, t_map *env)
{
	int 	built_in_status;
	char	**environment;

	environment = env->to_string(env);
	built_in_status = 0;
	if (ft_strchr(cmd->args[0], '/'))
		execve(cmd->args[0], cmd->args, environment);
	else
	{
		built_in_status = is_built_in(env, cmd);
		if (built_in_status != -1)
			env->put(env, ft_strdup("?"), ft_itoa(built_in_status), true); //alterar para false dps que tiver a expansao
		else
			execve(cmd->path, cmd->args, environment);
	}
	clear_matriz(environment);
}

void	handle_command(t_map *env, t_command *cmd, t_exec *exec)
{
	ft_printf("in: %d, out %d\n", exec->in, exec->out);
	if (!cmd->next && cmd->exec->len == 1)
		if (single_built_in(cmd, env) != -1)
			return ;
	cmd->pid = fork();
	if (cmd->pid < 0)
		printf("ERROR: fork()\n");
	else if (cmd->pid == 0)
	{
		child_signal();
		dup2(exec->in, STDIN_FILENO);
		dup2(exec->out, STDOUT_FILENO);
		close_fds(cmd->exec);
		execute_command(cmd, env);
		exec_failure(env, cmd, &exec->in, &exec->out);
		ft_exit(env, cmd, 1);
	}
	wait_all(cmd, env);
	if (!cmd->next)
		ft_close(&exec->fds[0]);
	ft_close(&exec->fds[1]);
		// close_fds(cmd->exec);
}