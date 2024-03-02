#include "minitalk_bonus.h"

static void handle_signal_bonus(int sig, siginfo_t *siginfo, void *context)
{
    static t_list   *binary_data = NULL;
    int array[8];
    static int count = 0;

    if (sig == SIGUSR1)
        array[count++] = 0;
    else if (sig == SIGUSR2)
        array[count++] = 1;
    if (count == 8)
        storelist_and_process(array, &binary_data, &count);
}

int main(void)
{
    struct sigaction act;

    ft_printf_basic("Server's pid is %d\n", getpid());
    ft_printf_basic("Waiting message...\n");
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal_bonus;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    while (1)
    {
        pause();
    }
}