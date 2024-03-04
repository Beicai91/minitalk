#include "minitalk_bonus.h"

void free_lst(t_list **binary_data)
{
    t_list  *temp;

    while (*binary_data != NULL)
    {
        temp = *binary_data;
        *binary_data = (*binary_data)->next;
        free(temp->content);
        free(temp);
    }
}

void storelist_and_process(int *array, t_list **binary_data, int *count, pid_t *c_pid)
{
    t_list  *node;
    int *array_ptr;
    int i;
    t_list **temp;

    array_ptr = malloc(sizeof(int) * 8);
    if (!array_ptr)
        exit(1);
    i = -1;
    while (++i < 8)
        array_ptr[i] = array[i];
    //test
    //for (int i = 0; i < 8; i++)
        //ft_printf_basic("%d ", array[i]);
    //ft_printf_basic("\n");
    //
    node = ft_lstnew(array_ptr);
    if (!node)
        exit(1);
    ft_lstadd_back(binary_data, node);
    if (check_null(array) == 1)
    {
        process_data(*binary_data);
        temp = binary_data;
        free_lst(temp);
        *binary_data = NULL;
        *c_pid = 0;
    }
    *count = 0;
}

void handle_signal_bonus(int sig, siginfo_t *siginfo, void *context)
{
    (void)siginfo;
    (void)context;
    static t_list   *binary_data = NULL;
    static int array[8];
    static int count = 0;
    static pid_t c_pid = 0;

    if (sig == SIGUSR1)
        array[count++] = 0;
    else if (sig == SIGUSR2)
        array[count++] = 1;
    if (!c_pid)
        c_pid = siginfo->si_pid;
    if (count == 8)
    {
        storelist_and_process(array, &binary_data, &count, &c_pid);
        kill(c_pid, SIGUSR1);
    }
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
        pause();
}

//the first message ok, the second isnt printed out normally