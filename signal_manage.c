// #include "minishell.h"

// void    signal_handler(int signo)
// {
//     if (signo == SIGINT)
//     {
//         write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
//     }
//     if (signo == SIGQUIT)
//     {
//         rl_on_new_line();
// 		rl_redisplay();
//     }
// }

// void    signal_init(void)
// {
//     signal(SIGINT, signal_handler);
//     signal(SIGQUIT, signal_handler);
// }
