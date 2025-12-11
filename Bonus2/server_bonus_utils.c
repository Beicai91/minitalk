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

int	check_null(int *array)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (array[i] != 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_bytes(t_list *temp)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (((int *)(temp->content))[i] == 0)
		return (1);
	else if (((int *)(temp->content))[i] == 1)
	{
		while (((int *)(temp->content))[i] == 1)
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	get_c(t_list *temp)
{
	int	c;
	int	i;

	i = 0;
	c = 0;
	while (i < 8)
	{
		c = (c << 1) | ((int *)(temp->content))[i];
		i++;
	}
	return (c);
}

void	get_str(char *str, t_list *binary_data)
{
	t_list	*temp;
	int		bytes;
	int		i;

	i = 0;
	temp = binary_data;
	while (temp != NULL)
	{
		bytes = check_bytes(temp);
		str[i++] = get_c(temp);
		if (bytes != 1)
		{
			while (bytes - 1 > 0)
			{
				temp = temp->next;
				str[i++] = get_c(temp);
				bytes--;
			}
		}
		temp = temp->next;
	}
}
