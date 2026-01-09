#include "minishell.h"

void sigint_handler(int signal)
{
	(void) signal;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void signals_init()
{
	struct sigaction sa_int;
    // struct sigaction sa_quit;

    sa_int.sa_handler = sigint_handler;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    // sa_quit.sa_handler = SIG_IGN;
    // sigemptyset(&sa_quit.sa_mask);
    // sa_quit.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa_int, NULL);
	// sigaction(SIGQUIT, &sa_quit, NULL);
    signal(SIGQUIT, SIG_IGN);	
}

void child_signal()
{
    signal(SIGQUIT, SIG_DFL);
}