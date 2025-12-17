#include "minishell.h"

void wait_all(t_command *cmd)
{
	while (cmd)
	{
		wait(NULL);
		cmd = cmd->next;
	}
}

