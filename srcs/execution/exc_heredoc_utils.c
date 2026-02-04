#include "minishell.h"

int heredoc_event_hook(void)
{
    if (g_sig == SIGINT)
        rl_done = 1; 
    return (0);
}

void handle_heredoc_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sigint);
	rl_event_hook = heredoc_event_hook;
	rl_catch_signals = 0; 
}

static bool	has_single_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

char	*clean_limiter(t_redirect *redir, bool *expand_vars)
{
	char	*limiter;
	char 	*raw;

	raw = redir->filename;
	*expand_vars = !has_single_quotes(raw);
	limiter = remove_quotes(raw);
	return (limiter);
}