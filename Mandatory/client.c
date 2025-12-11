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

#include "minitalk.h"

void	send_to_server(pid_t server_pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i & 1) == 0)
			kill(server_pid, SIGUSR1);
		else if ((c >> i & 1) == 1)
			kill(server_pid, SIGUSR2);
		usleep(100);
		i--;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	int		i;

	if (argc != 3)
	{
		ft_printf_basic("Error: wrong format for sending the message.\n");
		ft_printf_basic("Try ./client server_pid \"message\"\n");
		return (1);
	}
	else
	{
		i = -1;
		server_pid = ft_atoi(argv[1]);
		while (argv[2][++i])
			send_to_server(server_pid, argv[2][i]);
		send_to_server(server_pid, '\n');
	}
	return (0);
}
