/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aer-razk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:24:10 by aer-razk          #+#    #+#             */
/*   Updated: 2022/03/12 13:24:11 by aer-razk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minitalk.h"
#include <string.h>

int	g_cmp = 0;

int	su(int x, int y)
{
	int	i;
	int	j;

	i = -1;
	j = 1;
	while (++i < y)
		j = j * x;
	return (j);
}

void	ft_putnbr_fd(int n)
{
	long int	k;

	k = n;
	if (k < 0)
	{
		write(1, "-", 1);
		k = -k;
	}
	if (k >= 0)
	{
		if (k < 10)
			write (1, &"0123456789"[k], 1);
		else
		{
			ft_putnbr_fd(k / 10);
			write(1, &"0123456789"[k % 10], 1);
		}
	}
}

void	badsignalhandling(int signaltype, int *i, int *cpid, int pid)
{
	(*i) = 0;
	g_cmp = 0;
	(*cpid) = pid;
	if (g_cmp < 7)
	{
		if (signaltype == SIGUSR2)
			(*i) = (*i) + su(2, 6 - g_cmp);
		g_cmp++;
	}
	if (g_cmp == 7)
	{
		write(1, i, 1);
		(*i) = 0;
		g_cmp = 0;
	}
}

void	handlingsignal(int signaltype, siginfo_t *info, void *context)
{
	static int	i = 0;
	static int	cpid;

	(void)context;
	if (i == 0 && g_cmp == 0)
		cpid = info->si_pid;
	if (info->si_pid == cpid)
	{
		if (g_cmp < 7)
		{
			if (signaltype == SIGUSR2)
				i = i + su(2, 6 - g_cmp);
			g_cmp++;
		}
		if (g_cmp == 7)
		{
			write(1, &i, 1);
			i = 0;
			g_cmp = 0;
		}
	}
	else if (info->si_pid != cpid)
		badsignalhandling(signaltype, &i, &cpid, info->si_pid);
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	pid = getpid();
	action.__sigaction_u.__sa_sigaction = handlingsignal;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	ft_putnbr_fd(pid);
	write(1, "\n", 1);
	while (1)
		pause();
}
