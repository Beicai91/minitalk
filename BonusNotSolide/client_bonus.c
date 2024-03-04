#include "minitalk.h"

void    handle_signal(int sig, siginfo_t *siginfo, void *context)
{
    (void)sig;
    (void)siginfo;
    (void)context;
    ft_printf_basic("One byte sent successfully.\n");
}

void    send_to_server(pid_t server_pid, char c)
{
    int i;

    i = 7;
    while (i >= 0)
    {
        if ((c >> i & 1) == 0)
            kill(server_pid, SIGUSR1);
        else if ((c >> i & 1) == 1)
            kill(server_pid, SIGUSR2);
        usleep(100);
        i--;
    }
}

int main(int argc, char *argv[])
{
    struct sigaction    act;
    int i;

    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    if (argc != 3)
    {
        ft_printf_basic("Error: wrong format for sending the message.\n");
        ft_printf_basic("Try ./client_bonus server_pid \"message\"\n");
        return (1);
    }
    else
    {
        i = -1;
        while (argv[2][++i])
            send_to_server(ft_atoi(argv[1]), argv[2][i]);
        send_to_server(ft_atoi(argv[1]), '\n');
    }
    return (0);
}