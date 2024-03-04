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

#include "minitalk_bonus.h"

void	free_lst(t_list **binary_data)
{
	t_list	*temp;

	while (*binary_data != NULL)
	{
		temp = *binary_data;
		*binary_data = (*binary_data)->next;
		free(temp->content);
		free(temp);
	}
}

void	storelist_and_process(int *array, t_list **binary_data, pid_t *c_pid)
{
	t_list	*node;
	int		*array_ptr;
	int		i;

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
		process_data(*binary_data, *c_pid);
		free_lst(binary_data);
		*c_pid = 0;
	}
}

void	handle_signal_bonus(int sig, siginfo_t *siginfo, void *context)
{
	static t_list	*binary_data = NULL;
	static int		array[8];
	static int		count = 0;
	static pid_t	c_pid = 0;

	(void)context;
	if (sig == SIGUSR1)
		array[count++] = 0;
	else if (sig == SIGUSR2)
		array[count++] = 1;
	if (!c_pid)
		c_pid = siginfo->si_pid;
	if (count == 8)
	{
		count = 0;
		storelist_and_process(array, &binary_data, &c_pid);
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf_basic("Server's pid is %d\n", getpid());
	ft_printf_basic("Waiting message...\n");
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = handle_signal_bonus;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
