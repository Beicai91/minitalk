/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caibei <caibei@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:47:13 by bcai              #+#    #+#             */
/*   Updated: 2025/12/12 00:19:24 by caibei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../lib/libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

// client
void	send_to_server(pid_t server_pid, char c);

// server
void	handle_signal(int sig, siginfo_t *siginfo, void *context);

#endif