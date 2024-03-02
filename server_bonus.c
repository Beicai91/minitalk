#include "minitalk_bonus.h"

void storelist_and_process(int *array, t_list **binary_data, int *count)
{
    t_list  *node;
    int *array_ptr;
    int i;

    array_ptr = malloc(sizeof(int) * 8);
    if (!array_ptr)
        exit(1);
    i = -1;
    while (++i < 8)
        array_ptr[i] = array[i];
    node = ft_lstnew(array_ptr);
    if (!node)
        exit(1);
    ft_lstadd_back(binary_data, node);
    if (check_null(array) == 1)
    {
        process_data(*binary_data);
        *binary_data = NULL;
    }
    *count = 0;
}

void handle_signal_bonus(int sig, siginfo_t *siginfo, void *context)
{
    (void)siginfo;
    (void)context;
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