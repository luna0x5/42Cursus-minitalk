/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 21:13:30 by hmoukit           #+#    #+#             */
/*   Updated: 2024/05/08 17:10:01 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_sig(char c, int pid, int j)
{
	if (pid <= 0)
		exit(1);
	if ((c >> j) & 1)
	{
		if (kill(pid, SIGUSR2) < 0)
			exit(1);
	}
	else
	{
		if (kill(pid, SIGUSR1) < 0)
			exit(1);
	}
}

int	main(int ac, char **av)
{
	int	i;
	int	j;
	int	pid;

	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		i = 0;
		while (av[2][i])
		{
			j = 7;
			while (j >= 0)
			{
				send_sig(av[2][i], pid, j);
				j--;
				usleep(500);
			}
			i++;
		}
	}
	return (0);
}
