#include "minishell.h"

static int	path_look_up(t_command *cmd, char **env)
{
	struct stat	st;

	if (ft_strchr(cmd->args[0], '/'))
	{
		if (stat(cmd->args[0], &st) != 0)
		{
			ft_putstr_fd(cmd->args[0], 2);
			return (ft_putstr_fd(": No such file or directory\n", 2), 127);
		}
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(cmd->args[0], 2);
			return (ft_putstr_fd(": Is a directory\n", 2), 126);
		}
		if (S_ISREG(st.st_mode))
		{
			if (access(cmd->path, X_OK) != 0)
			{
				ft_putstr_fd(cmd->args[0], 2);
				return (ft_putstr_fd(": Permission denied\n", 2), 126);
			}
		}
		execve(cmd->args[0], cmd->args, env);
	}
	return (0);
}

static void	exec_failure(t_map *env, t_command *cmd, t_exec *exec)
{
	ft_putstr_fd(*cmd->args, 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fds(exec, cmd, false);
	ft_exit(env, cmd, exec, 127);
}

static int	single_built_in(t_command *cmd, t_map *env, t_exec *exec)
{
	int	built_in_status;

	built_in_status = is_built_in(env, cmd, exec);
	if (built_in_status != -1)
		env->put(env, ft_strdup("?"), ft_itoa(built_in_status), true);
	// alterar para false dps que tiver a expansao
	return (built_in_status);
}

static void	execute_command(t_command *cmd, t_map *env, t_exec *exec)
{
	char	**environment;
	int		built_in_status;
	int		path_status;

	built_in_status = 0;
	environment = env->to_string(env);
	path_status = path_look_up(cmd, environment);
	if (path_status > 0)
	{
		(clear_matriz(environment), close_fds(exec, cmd, false));
		ft_exit(env, cmd, exec, path_status);
	}
	else if (path_status == 0)
	{
		built_in_status = is_built_in(env, cmd, exec);
		if (built_in_status != -1)
		{
			env->put(env, ft_strdup("?"), ft_itoa(built_in_status), true);// alterar para false dps que tiver a expansao
			(clear_matriz(environment), close_fds(exec, cmd, false));
			ft_exit(env, cmd, exec, built_in_status);
		}
		else
			execve(cmd->path, cmd->args, environment);
	}
	clear_matriz(environment);
}

void	handle_command(t_map *env, t_command *cmd, t_exec *exec)
{
	if (!cmd->next && exec->len == 1)
		if (single_built_in(cmd, env, exec) != -1)
			return ;
	cmd->pid = fork();
	if (cmd->pid < 0)
		printf("ERROR: fork()\n");
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
 // ls | cat da erro
 