#include "minishell.h"

static void execute_script(t_command *cmd, char **env)
{
	char *args[3];

	args[0] = "sh";
	args[1] = cmd->args[0];
	args[2] = NULL;
	execve("/bin/sh", args, env);
}

static int	path_look_up(t_command *cmd, t_map *env)
{
	struct stat	st;
	char **environment;

	environment = NULL;
	if (ft_strchr(cmd->args[0], '/') || !env->get(env, "PATH"))
	{
		if (stat(cmd->args[0], &st) != 0)
			return (ft_dprintf(2, "Bash: %s: No such file or directory\n", cmd->args[0]), 127);
		if (S_ISDIR(st.st_mode))
			return (ft_dprintf(2, "Bash: %s: Is a directory\n", cmd->args[0]), 126);
		if (S_ISREG(st.st_mode))
			if (access(cmd->path, X_OK) != 0)
				return (ft_dprintf(2, "Bash: %s: Permission denied\n", cmd->args[0]), 126);
		environment = env->to_string(env);
		execve(cmd->args[0], cmd->args, environment);
		if (errno == ENOEXEC)
			execute_script(cmd, environment);
		clear_matriz(environment);
	}
	return (0);
}

static void	exec_failure(t_map *env, t_command *cmd, t_exec *exec)
{
	ft_dprintf(2, "%s: command not found\n", *cmd->args);
	close_fds(exec, cmd, false);
	ft_exit(env, cmd, exec, 127);
}

static int	single_built_in(t_command *cmd, t_map *env, t_exec *exec)
{
	int	built_in_status;

	exec->temp_in = dup(STDIN_FILENO);
	exec->temp_out = dup(STDOUT_FILENO);
	dup2(exec->in, STDIN_FILENO);
	dup2(exec->out, STDOUT_FILENO);
	built_in_status = is_built_in(env, cmd, exec);
	dup2(exec->temp_in, STDIN_FILENO);
	dup2(exec->temp_out, STDOUT_FILENO);
	ft_close(&exec->temp_in);
	ft_close(&exec->temp_out);
	return (built_in_status);
}

static void	execute_command(t_command *cmd, t_map *env, t_exec *exec)
{
	int		btin_sts;
	char 	**environment;
	int		path_status;

	btin_sts = 0;
	cmd->path = get_path(env, cmd->args);
	path_status = path_look_up(cmd, env);
	if (path_status > 0)
		(close_fds(exec, cmd, false), ft_exit(env, cmd, exec, path_status));
	else if (path_status == 0)
	{
		btin_sts = is_built_in(env, cmd, exec);
		if (btin_sts != -1)
			(close_fds(exec, cmd, false), ft_exit(env, cmd, exec, btin_sts));
		else
		{
			// if (!*cmd->path)
			// {
			// 	printf("entreiaki\n");
			// 	exec_failure(env, cmd, exec);
			// }
			environment = env->to_string(env);
			execve(cmd->path, cmd->args, environment);
			clear_matriz(environment);
		}
	}
}

void	handle_command(t_map *env, t_command *cmd, t_exec *exec)
{
	if (!cmd->next && exec->len == 1)
		if (single_built_in(cmd, env, exec) != -1)
			return ;
	cmd->pid = fork();
	if (cmd->pid < 0)
		perror(NULL);
	else if (cmd->pid == 0)
	{
		child_signal();
		dup2(exec->in, STDIN_FILENO);
		dup2(exec->out, STDOUT_FILENO);
		close_fds(exec, cmd, false);
		execute_command(cmd, env, exec);
		exec_failure(env, cmd, exec);
	}
	close_fds(exec, cmd, true);
}
 