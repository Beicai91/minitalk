#include "minitalk.h"

int add_num(int i)
{
    int result;

    result = 1;
    while (i > 0)
    {
        result *= 2;
        i--;
    }
    return (result);
}

void    handle_signal(int sig, siginfo_t *siginfo, void *context)
{
    static int  c = 0;
    static int  counter = 7;

    if (sig == SIGUSR2)
        c = c | add_num(counter);
    counter--;
    if (counter < 0)
    {
        ft_printf_basic("%c", c);
        c = 0;
        counter = 7;
    }
}

int main(void)
{
    struct sigaction act;

    ft_printf_basic("Server's pid is %d\n", getpid());
    ft_printf_basic("Waiting message...\n");
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    while (1)
    {
        pause();
    }
}