#include "minishell.h"

void	wait_all(t_command *cmd, t_map *env)
{
	t_command	*temp;
	int			status;
	int			exit_code;
	int			last_pid;

	temp = cmd;
	while (cmd->next)
		cmd = cmd->next;
	last_pid = cmd->pid;
	exit_code = 0;
	while (temp)
	{
		if (waitpid(temp->pid, &status, 0) > 0)
			if (last_pid == temp->pid)
			{
				if (WIFSIGNALED(status))
				{
					if (WTERMSIG(status) == SIGQUIT)
						write(2, "Quit (core dumped)\n", 20);
					if (WTERMSIG(status) == SIGINT)
					   	write(2, "\n", 1);
					exit_code = 128 + WTERMSIG(status);
				}
				if (WIFEXITED(status))
					exit_code = WEXITSTATUS(status);
			}
		temp = temp->next;
	}
	env->put(env, ft_strdup("?"), ft_itoa(exit_code), true);// alterar para false dps que tiver a expansao
}
