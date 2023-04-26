#include "minishell.h"

static void    signal_handler(int signo)
{
    if (signo == SIGINT)
    {
        write(1, "\n", 1);
		rl_on_new_line();
        rl_replace_line("", 1);
		rl_redisplay();
    }
    if (signo == SIGQUIT)
    {
        rl_on_new_line();
		rl_redisplay();
    }
}

void    signal_init(int sig_int, int sig_quit)
{
    if (sig_int == 0)
        signal(SIGINT, SIG_IGN);
    else if (sig_int == 1)
        signal(SIGINT, SIG_DFL);
    else
        signal(SIGINT, signal_handler);
    if (sig_quit == 0)
        signal(SIGQUIT, SIG_IGN);
    else if (sig_quit == 1)
        signal(SIGQUIT, SIG_DFL);
    else
        signal(SIGQUIT, signal_handler);
}
