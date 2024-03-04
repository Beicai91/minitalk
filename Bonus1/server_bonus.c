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

int	add_num(int i)
{
	int	result;

	result = 1;
	while (i > 0)
	{
		result *= 2;
		i--;
	}
	return (result);
}

void	handle_signal(int sig, siginfo_t *siginfo, void *context)
{
	static int		c = 0;
	static int		counter = 7;
	static pid_t	c_pid = 0;

	(void)siginfo;
	(void)context;
	if (sig == SIGUSR2)
		c = c | add_num(counter);
	counter--;
	if (counter < 0)
	{
		if (!c_pid)
			c_pid = siginfo->si_pid;
		ft_printf_basic("%c", c);
		kill(c_pid, SIGUSR1);
		c = 0;
		counter = 7;
		c_pid = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf_basic("Server's pid is %d\n", getpid());
	ft_printf_basic("Waiting message...\n");
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handle_signal;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
		pause();
	}
}
