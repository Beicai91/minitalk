/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcai <marvin@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:47:13 by bcai              #+#    #+#             */
/*   Updated: 2024/03/04 15:47:18 by bcai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

// client
void	send_to_server_bonus(pid_t server_pid, unsigned char c);
void	handle_signal(int sig, siginfo_t *siginfo, void *context);

// server
void	handle_signal_bonus(int sig, siginfo_t *siginfo, void *context);
void	storelist_and_process(int *array, t_list **binary_data, pid_t *c_pid);
void	process_data(t_list *binary_data, pid_t c_pid);
void	process_bytes(t_list *binary_data, int bytes_total, pid_t c_pid);
void	free_lst(t_list **binary_data);

// server_utils
void	get_str(char *str, t_list *binary_data);
int		get_c(t_list *temp);
int		check_bytes(t_list *temp);
int		check_null(int *array);

#endif