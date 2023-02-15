#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct Config {
	int delay;
};

void signal_handler(int sig)
{
	if (sig == SIGUSR1)
		printf("0\n");
	if (sig == SIGUSR2)
		printf("1\n");
}

int	main(int argc, char **argv)
{
	int pid;
	struct Config config;

	pid = getpid();
	config.delay = argv[1] ? atoi(argv[1]) : 0;
	printf("Server Pid: %d\n", pid);
	while (config.delay > 0)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		sleep(1);
		config.delay--;
	}
	printf("Done waiting\n");
}