/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:11:07 by hmoukit           #+#    #+#             */
/*   Updated: 2024/05/08 17:12:11 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	client_signal_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		if (write(1, "Message received by server.\n", 28) < 0)
			exit(1);
	}
}

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

void	send_msg(char **av, int pid)
{
	int	i;
	int	j;

	i = 0;
	while (av[2][i])
	{
		j = 7;
		while (j >= 0)
		{
			send_sig(av[2][i], pid, j);
			j--;
			usleep(400);
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int		j;
	int		pid;
	char	c;

	c = '\0';
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (signal(SIGUSR1, client_signal_handler) < 0)
			exit(1);
		send_msg(av, pid);
		j = 7;
		while (j >= 0)
		{
			send_sig(c, pid, j);
			j--;
			usleep(400);
		}
	}
	return (0);
}
