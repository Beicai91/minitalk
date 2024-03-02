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
    get_str(&str, binary_data);
    start = send_to_client(str) + 1;
    ft_printf_basic("%s", &str[start]);
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