#include "minitalk_bonus.h"

void process_bytes(t_list *binary_data, int bytes_total)
{
    char *str;

    (void)binary_data;
    str = (char *)malloc(sizeof(char) * bytes_total);
    if (!str)
        exit(1);
    get_str(str, binary_data);
    ft_printf_basic("%s\n", str);
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
    //test
    ft_printf_basic("total bytes received %d\n", bytes_total);
    //
    process_bytes(binary_data, bytes_total);
}
