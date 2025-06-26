/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 06:11:09 by hmoukit           #+#    #+#             */
/*   Updated: 2024/05/08 17:13:12 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	handle_unicode(char c, int *count, int z)
{
	static char	buffer[4];
	static int	i;

	if (z == 1)
	{
		initialize_buffer(&buffer);
		i = 0;
	}
	if (*count > 1)
	{
		buffer[i] = c;
		i++;
		if (i == *count)
		{
			if (write(1, buffer, i) < 0)
				exit(1);
			i = 0;
			*count = 0;
			initialize_buffer(&buffer);
		}
	}
}

void	make_sig(char **c, int *k, int sig)
{
	if (sig == SIGUSR1)
		**c += 0 << *k;
	else
		**c += 1 << *k;
}

void	make_char(char *c, int sig, int *k, pid_t c_pid)
{
	static int	count = 0;

	make_sig(&c, k, sig);
	(*k)--;
	if (*k == -1)
	{
		if (count == 0)
			count = check_byte(*c, &count);
		if (count == 1)
		{
			if (write(1, &(*c), 1) < 0)
				exit(1);
			count = 0;
			send_back_sig(*c, c_pid);
		}
		else if (count > 1)
		{
			handle_unicode(*c, &count, 0);
			send_back_sig(*c, c_pid);
		}
		*c = 0;
		*k = 7;
	}
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static char		c = 0;
	static int		k = 7;
	static pid_t	client_pid = -1;
	int				count;

	count = 0;
	(void)context;
	if (client_pid == -1)
		client_pid = info->si_pid;
	else if (client_pid != info->si_pid)
	{
		c = 0;
		k = 7;
		handle_unicode(c, &count, 1);
		client_pid = info->si_pid;
	}
	make_char(&c, sig, &k, client_pid);
}

int	main(void)
{
	struct sigaction	newact;
	pid_t				pid;

	newact.sa_sigaction = signal_handler;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = SA_SIGINFO;
	pid = getpid();
	if (write(1, "\n----- the Process ID of the server -----\n\t\t", 44) < 0)
		exit(1);
	ft_putnbr_fd(pid, 1);
	if (write(1, "\n", 1) < 0)
		exit(1);
	while (1)
	{
		if (sigaction(SIGUSR1, &newact, NULL) < 0)
			exit(1);
		if (sigaction(SIGUSR2, &newact, NULL) < 0)
			exit(1);
		pause();
	}
	return (0);
}
