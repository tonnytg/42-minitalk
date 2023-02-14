#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct Config {
	int delay;
};

void signal_handler(int sig)
{
	// decode signal
	sigset_t set;
	struct sigaction act;

	set = 1 >> (sig + 1);
	sigemptyset(&set);
	sigaddset(&set, sig);
	act.sa_mask = set;
	act.sa_flags = 0;
	act.__sigaction_u.__sa_handler = NULL;
	sigaction(sig, &act, NULL);

	printf("Received signal: %d\n", sig);
}

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
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		sleep(1);
		config.delay--;
	}
	printf("Done waiting\n");
}