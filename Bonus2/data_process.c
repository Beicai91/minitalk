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

void	process_bytes(t_list *binary_data, int bytes_total, pid_t c_pid)
{
	char	*str;

	(void)binary_data;
	str = (char *)malloc(sizeof(char) * bytes_total);
	if (!str)
		exit(1);
	get_str(str, binary_data);
	ft_printf_basic("%s\n", str);
	free(str);
	kill(c_pid, SIGUSR1);
}

void	process_data(t_list *binary_data, pid_t c_pid)
{
	t_list	*temp;
	int		bytes_total;

	temp = binary_data;
	bytes_total = 0;
	while (temp != NULL)
	{
		bytes_total++;
		temp = temp->next;
	}
	process_bytes(binary_data, bytes_total, c_pid);
}
