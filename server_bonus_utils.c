#include "minitalk_bonus.h"

int  check_null(int *array)
{
    int i;

    i = 0;
    while (i < 8)
    {
        if (array[i] != 0)
            return (0);
        i++;
    }
    return (1);
}

int check_bytes(t_list *temp)
{
    int count;
    int i;

    count = 0;
    i = 0;
    if (((int *)(temp->content))[i] == 0)
        return (1);
    else if (((int *)(temp->content))[i] == 1)
    {
        while (((int *)(temp->content))[i] == 1)
        {
            count++;
            i++;
        }
    }
    return (count);
}

int get_c(t_list *temp)
{
    int c;
    int i;

    i = 0;
    c = 0;
    while (i < 8)
    {
        c = (c << 1) | ((int *)(temp->content))[i];
        i++;
    }
    return (c);
}

int  send_to_client(char *str)
{
    int i;
    int j;
    char    *pid_str;

    i = 0;
    while (str[i] != '\n')
        i++;
    pid_str = malloc(sizeof(char) * (i + 1));
    if (!pid_str)
        exit(1);
    j = -1;
    while (str[++j] != '\n')
        pid_str[j] = str[j];
    pid_str[j] = '\0';
    kill(ft_atoi(pid_str), SIGUSR1);
    free(pid_str);
    return (i);
}

void get_str(char **str, t_list *binary_data)
{
    t_list  *temp;
    int bytes;
    int i;

    i = 0;
    temp = binary_data;
    while (temp != NULL)
    {
        bytes = check_bytes(temp);
        (*str)[i++] = get_c(temp);
        if (bytes != 1)
        {
            while (bytes - 1 > 0)
            {
                temp = temp->next;
                (*str)[i++] = get_c(temp);
                bytes--;
            }
        }
        temp = temp->next;
    }
}