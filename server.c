#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler(int signal)
{
	if (signal == SIGINT) {
		printf("Received SIGINT %d\n", signal);
		exit(0);
	}
	else if (signal == SIGUSR1)
		printf("Received SIGUSR1 %d\n", signal);
	else if (signal == SIGUSR2)
		printf("Received SIGUSR2 %d\n", signal);
}


int main(void) {
	printf("Server is running, PID: %d\n", getpid());
	while (1) {
		signal(SIGINT, signal_handler);
	}
}