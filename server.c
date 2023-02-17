#include "ft_minitalk.h"
#include <stdio.h>

int	math_pow(int i)
{
	int	nb;

	nb = 128;
	while (i < 7)
	{
		nb = nb / 2;
		i++;
	}
	return (nb);
}

static void	signal_handler(int sign, siginfo_t *signalfo, void *oldact)
{
	static int				i;
	static unsigned char	count;
	static int				actpid;

	(void)oldact;
	if (actpid != signalfo->si_pid)
	{
		actpid = signalfo->si_pid;
		i = 7;
		count = 0;
	}
	if (sign == SIGUSR2)
	{
		count = count + math_pow(i);
	}
	i--;
	if (i == -1)
	{
		printf("%c", count);
		i = 7;
		count = 0;
	}
}

int	main(void)
{
	struct sigaction	act;
	int					pid;

	act.sa_sigaction = signal_handler;
	pid = getpid();
	printf("pid: %d\n", pid);
	printf("RECEIVED MESSAGES\n\n");
	while (1)
	{
		sigaction(SIGUSR1, &act, NULL);
		sigaction(SIGUSR2, &act, NULL);
		pause();
	}
	return (0);
}