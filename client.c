#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int	main(int argc, char **argv)
{
	int p;
	int err;
	int msg;
	sigset_t set;
	struct sigaction act;

	if (argc <= 2)
	{
		printf("Usage: <PID> Message\n");
		return 1;
	}
	p = atoi(argv[1]);
	msg = atoi(argv[2]);

	set = 1 << (msg - 1);
	sigemptyset(&set);
	sigaddset(&set, msg);
	act.sa_mask = set;
	act.sa_flags = 0;
	act.__sigaction_u.__sa_handler = NULL;
	err = sigaction(msg, &act, NULL);
	if (err)
	{
		printf("Error: %d\n", err);
		return 1;
	}

	printf("Sending message to PID: %d\nMSG:%d\n", p, msg);
	return 0;
}
