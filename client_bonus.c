#include "minitalk_bonus.h"

void    send_to_server_bonus(pid_t server_pid, unsigned char c)
{
    int i;

    i = 7;
    while (i >= 0)
    {
        if ((c >> i & 1) == 0)
            kill(server_pid, SIGUSR1);
        else if ((c >> i & 1) == 1)
            kill(server_pid, SIGUSR2);
        usleep(500);
        i--;
    }
}

void    handle_signal(int sig, siginfo_t *siginfo, void *context)
{
    (void)sig;
    (void)siginfo;
    (void)context;
    ft_printf_basic("A byte sent successfully to the server.\n");
}

int main(int argc, char *argv[])
{
    pid_t   server_pid;
    struct sigaction    act;
    int i;

    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    if (argc != 3)
    {
        ft_printf_basic("Error: wrong format.\n Try ./client_bonus server_pid \"message\"\n");
        return (1);
    }
    else
    {
        i = -1;
        server_pid = ft_atoi(argv[1]);
        while (argv[2][++i])
            send_to_server_bonus(server_pid, (unsigned char)argv[2][i]);
        send_to_server_bonus(server_pid, '\0');
    }
    return (0);
}