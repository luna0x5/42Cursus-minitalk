/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:12:14 by hmoukit           #+#    #+#             */
/*   Updated: 2024/05/08 17:10:21 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	if (write(fd, &c, 1) < 0)
		exit(1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n >= 0 && n <= 9)
		ft_putchar_fd(n + '0', fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			ft_putnbr_fd(147483648, fd);
		}
		else
		{
			n *= -1;
			ft_putnbr_fd(n, fd);
		}
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}

static int	handle_overflow(const char *str, int sign, long result)
{
	long	nbr;
	size_t	i;

	nbr = 0;
	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		nbr = result * 10 + (str[i] - '0');
		if (nbr < result)
		{
			if (sign < 0)
				return (0);
			else if (sign > 0)
				return (-1);
		}
		result = nbr;
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= (-1);
		i++;
	}
	result = handle_overflow(str + i, sign, result);
	return (result);
}
