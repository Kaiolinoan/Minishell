// #include "minishell.h"
// int g_exit_code = 0;

// void sigint_handler(int signal)
// {
// 	(void) signal;
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }
// void sigquit_handler(int signal)
// {
// 	(void) signal;
// 	write(STDOUT_FILENO, "entrou aqui\n", 13);
// }

// #include <signal.h>
// #include <stdio.h>

// void debug_signal_action() {
//     struct sigaction sa;
//     if (sigaction(SIGQUIT, NULL, &sa) == 0) {
//         if (sa.sa_handler == SIG_IGN)
//             printf("SIGQUIT is ignored\n");
//         else if (sa.sa_handler == SIG_DFL)
//             printf("SIGQUIT is set to default action\n");
//         else
//             printf("SIGQUIT has a custom handler\n");
//     } else {
//         perror("Failed to get SIGQUIT handler settings");
//     }
// }

// // Call this in main():

// int	main(int argc, char **argv, char **environment)
// {
// 	char		*str;

// 	(void)argv;
// 	(void)environment;

// 	if (argc > 1)
// 		return (0);

//     struct sigaction sa_int;
//     struct sigaction sa_quit;

//     sa_int.sa_handler = sigint_handler;
//     sigemptyset(&sa_int.sa_mask);
//     sa_int.sa_flags = SA_RESTART;
// 	//Sig_IGN
//     sa_quit.sa_handler = SIG_IGN;
//     sigemptyset(&sa_quit.sa_mask);
//     sa_quit.sa_flags = SA_RESTART;
// 	rl_catch_signals = 0;
	
// 	while (1)
// 	{
// 		sigaction(SIGQUIT, &sa_quit, NULL);	
// 		sigaction(SIGINT, &sa_int, NULL);
// 		debug_signal_action();
// 		str = readline("minishell> ");
// 		if (!str)
// 			break ;
// 		if (*str)
// 			add_history(str);
// 	}
// 	printf("Saindo do minishell!\n");
// }