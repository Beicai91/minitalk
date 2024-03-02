#ifndef MINITALK_H
# define MINITALK_H

#include "libft/libft.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

//client
void    send_to_server(pid_t server_pid, char c);

//server
void    handle_signal(int sig, siginfo_t *siginfo, void *context);
int add_num(int i);

#endif