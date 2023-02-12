#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int	main(int argc, char **argv)
{
	int p;
	int err;
	int msg;

	if (argc < 2)
	{
		printf("Usage: <PID> Message");
		return 1;
	}
	p = atoi(argv[1]);
	msg = atoi(argv[2]);
	printf("Sending message to PID: %d\nMSG:%d\n", p, msg);
	err = kill(p, msg);
	sigaction(SIGUSR1, NULL, NULL);
	if (err == -1)
	{
		printf("Error sending message\n");
		return 1;
	}
	printf("kill sent\n");
}
