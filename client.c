/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 23:31:58 by antthoma          #+#    #+#             */
/*   Updated: 2023/02/17 15:42:48 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_control;

void	error_sent(void)
{
	ft_putstr_fd("error to sent\n", 1);
	exit(1);
}

void	send_sig(char *bits, int pid)
{
	int	n;

	n = 0;
	while (bits[n])
	{
		if (bits[n] == '0')
		{
			if (kill(pid, SIGUSR1) == -1)
				error_sent();
		}
		else if (bits[n] == '1')
		{
			if (kill(pid, SIGUSR2) == -1)
				error_sent();
		}
		while (g_control == 0)
			;
		g_control = 0;
		n++;
	}
}

void	char_to_bit(int dec, int pid)
{
	char	bits[9];
	int		i;

	ft_bzero(bits, 9);
	i = 7;
	while (i >= 0)
	{
		if (dec % 2 == 0)
			bits[i] = '0';
		else
			bits[i] = '1';
		i--;
		dec = dec / 2;
	}
	send_sig(bits, pid);
}

void	client_handler(int signal)
{
	if (signal == SIGUSR2)
		g_control = 1;
	else if (signal == SIGUSR1)
	{
		ft_putstr_fd("done\n", 1);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_sa;
	pid_t				pid;
	int					i;

	i = 0;
	pid = 0;
	if (argc != 3 || ft_strisdigit(argv[1]) <= 0)
	{
		ft_putstr_fd("./client PID MSG\n", 1);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	ft_bzero(&s_sa, sizeof(struct sigaction));
	s_sa.sa_handler = client_handler;
	if (sigaction(SIGUSR2, &s_sa, NULL))
		exit(1);
	if (sigaction(SIGUSR1, &s_sa, NULL))
		exit(1);
	while (i < (int)ft_strlen(argv[2]))
	{
		char_to_bit((int)argv[2][i], pid);
		i++;
	}
	char_to_bit(0, pid);
	return (0);
}
