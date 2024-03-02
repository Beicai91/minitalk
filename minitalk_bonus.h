#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

#include "libft/libft.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

//client
void    send_to_server_bonus(pid_t server_pid, unsigned char c);
void    communicate_pid(pid_t client_pid, pid_t server_pid);
void    handle_signal(int sig, siginfo_t *siginfo, void *context);

//server
void handle_signal_bonus(int sig, siginfo_t *siginfo, void *context);
void storelist_and_process(int *array, t_list **binary_data, int *count);
void process_data(t_list *binary_data);
void process_bytes(t_list *binary_data, int bytes_total);
void free_lst(t_list *binary_data);

//server_utils
void get_str(char *str, t_list *binary_data);
int  send_to_client(char *str);
int get_c(t_list *temp);
int check_bytes(t_list *temp);
int  check_null(int *array);

#endif