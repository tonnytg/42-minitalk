/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 23:31:58 by antthoma          #+#    #+#             */
/*   Updated: 2023/02/17 15:39:14 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	bits_to_decimal(t_bits *bit)
{
	unsigned int	decimal;
	int				i;

	decimal = 0;
	i = 0;
	while (bit->bits[i])
	{
		if (bit->bits[i] == '1')
			decimal += ft_pow(2, 7 - i);
		i++;
	}
	return (decimal);
}

void	server_handler(int signum, siginfo_t *info, void *context)
{
	static t_bits	b;
	char			charac[1];

	if (signum == SIGUSR1)
		b.bits[b.n] = '0';
	else if (signum == SIGUSR2)
		b.bits[b.n] = '1';
	if (b.n == 7)
	{
		b.n = 0;
		charac[0] = (unsigned char)bits_to_decimal(&b);
		ft_putchar_fd(*charac, 1);
		if (bits_to_decimal(&b) == 0)
		{
			ft_putstr_fd("\n", 1);
			kill(info->si_pid, SIGUSR1);
		}			
	}
	else
		b.n++;
	if (kill(info->si_pid, SIGUSR2))
		exit (1);
	(void)context;
}

int	main(void)
{
	struct sigaction	sa;
	sigset_t			mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	sa.sa_mask = mask;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = server_handler;
	if (sigaction(SIGUSR1, &sa, NULL))
		exit(1);
	if (sigaction(SIGUSR2, &sa, NULL))
		exit(1);
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	while (1)
		pause();
	return (0);
}
