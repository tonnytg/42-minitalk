#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct Config {
	int delay;
};

int	main(int argc, char **argv)
{
	int pid;
	struct Config config;

	pid = getpid();
	config.delay = argv[1] ? atoi(argv[1]) : 0;
	printf("Delay: %d\n", config.delay);
	while (config.delay > 0)
	{
		printf("Waiting for %d seconds - pid: %d\n", config.delay, pid);
		sleep(1);
		config.delay--;
	}
	printf("Done waiting\n");
}