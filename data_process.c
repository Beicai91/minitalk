#include "minitalk_bonus.h"

void free_lst(t_list *binary_data)
{
    t_list  *temp;

    while (binary_data != NULL)
    {
        temp = binary_data;
        binary_data = binary_data->next;
        free(temp->content);
        free(temp);
    }
}

void process_bytes(t_list *binary_data, int bytes_total)
{
    char *str;
    int start;

    str = (char *)malloc(sizeof(char) * bytes_total);
    if (!str)
        exit(1);
    get_str(str, binary_data);
    start = send_to_client(str) + 1;
    ft_printf_basic("%s\n", &str[start]);
    free(str);
}

void process_data(t_list *binary_data)
{
    t_list  *temp;
    int bytes_total;

    temp = binary_data;
    bytes_total = 0;
    while (temp != NULL)
    {
        bytes_total++;
        temp = temp->next;
    }
    process_bytes(binary_data, bytes_total);
    free_lst(binary_data);
}
