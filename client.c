#include "ft_minitalk.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	convert(int nb, char *bit)
{
	int	i;

	i = 0;
	if (nb == 0 || nb == 1)
	{
		while (i < 7)
		{
			bit[i] = bit[i + 1];
			i++;
		}
		bit[7] = nb + '0';
	}
	else
	{
		convert(nb / 2, bit);
		convert(nb % 2, bit);
	}
}

void	sended_str( char *pid, int nb)
{
	int		i;
	char	*bit;

	i = 0;
	bit = strdup("00000000");
	convert(nb, bit);
	while (i < 8)
	{
		if (bit[i] == '1')
			kill(atoi(pid), SIGUSR2);
		if (bit[i] == '0')
			kill(atoi(pid), SIGUSR1);
		i++;
		usleep(100);
	}
	free(bit);
}

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (kill(atoi(av[1]), 0) == -1)
	{
		printf("OPPPS!! WRONG PID, TRY AGAIN :/\n");
		return (0);
	}
	if (ac >= 3)
	{
		while (av[2][i])
		{
			sended_str(av[1], (unsigned char)av[2][i]);
			i++;
		}
		printf("MESSAGE SENT SUCCESSFULLY ✔:) \n");
	}
	else
	{
		printf("MESSAGE CANT BE SENT \n");
		printf("BAD SYNTAX:---> ./client <server_pid> + <text to send>\n");
	}
	return (0);
}