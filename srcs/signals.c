#include "../includes/minishell.h"

void	sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    g_last_exit_status = 130;
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN); // Ctrl+
}
