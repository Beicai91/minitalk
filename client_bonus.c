
#include "minitalk_bonus.h"


void    send_to_server_bonus(pid_t server_pid, unsigned char c)
{
    int i;

    i = 7;
    while (i >= 0)
    {
        if ((c >> i & 1) == 0)
        //{
            //test
            //ft_printf_basic("Send signal 0\n");
        //
            kill(server_pid, SIGUSR1);
        //}
        else if ((c >> i & 1) == 1)
        //{
            //test
            //ft_printf_basic("Send signal 1\n");
            kill(server_pid, SIGUSR2);
        //}
        usleep(100);
        i--;
    }
}

void    communicate_pid(pid_t client_pid, pid_t server_pid)
{
    char    *pid_str;
    int i;

    pid_str = ft_itoa((int)client_pid);
    i = -1;
    //test
    //ft_printf_basic("communicating client pid...");
    //
    while (pid_str[++i])
        send_to_server_bonus(server_pid, (unsigned char)pid_str[i]);
    send_to_server_bonus(server_pid, '\n');
    free(pid_str);
}

void    handle_signal(int sig, siginfo_t *siginfo, void *context)
{
    (void)sig;
    (void)siginfo;
    (void)context;
    ft_printf_basic("Message sent successfully.");
    exit(0);
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
    if (argc != 3)
    {
        ft_printf_basic("Error: wrong format.\n Try ./client_bonus server_pid \"message\"\n");
        return (1);
    }
    else
    {
        i = -1;
        server_pid = ft_atoi(argv[1]);
        //test
        //ft_printf_basic("client pid is %d\n", (int)client_pid);
        //
        communicate_pid(getpid(), server_pid);
        //test
        //ft_printf_basic("sending message content...");
        //
        while (argv[2][++i])
            send_to_server_bonus(server_pid, (unsigned char)argv[2][i]);
        send_to_server_bonus(server_pid, '\0');
    }
    while (1)
        pause();
    return (0);
}