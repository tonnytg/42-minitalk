#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	printf("Server is running, PID: %d\n", getpid());
	signal(SIGINT, SIG_IGN);
}