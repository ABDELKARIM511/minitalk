/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:23:55 by aer-razk          #+#    #+#             */
/*   Updated: 2022/03/12 13:23:58 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./minitalk.h"

int	ft_atoi(const char *str)
{
	char		*c;
	size_t		k;
	size_t		m;

	c = (char *)str;
	m = 1;
	k = 0;
	while (*c == ' ' || *c == '\n'
		|| *c == '\t' || *c == '\r'
		|| *c == '\f' || *c == '\v' )
	{
		c++;
	}
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			m = m * -1;
		c++;
	}
	while (*c >= '0' && *c <= '9')
	{
		k = (*c - 48) + k * 10;
		c++;
	}
	return ((int)(k * m));
}

void	sendsignal(int c, char *pid)
{
	int	i;

	i = 6;
	while (i >= 0)
	{
		if ((c >> i) % 2 == 0)
			kill(ft_atoi(pid), SIGUSR1);
		else if ((c >> i) % 2 == 1)
			kill(ft_atoi(pid), SIGUSR2);
		usleep(500);
		i--;
	}
}

int	main(int arc, char **arv)
{
	int	i;

	i = -1;
	if (arc == 3)
	{
		while (arv[2][++i])
			sendsignal(arv[2][i], arv[1]);
	}
}
