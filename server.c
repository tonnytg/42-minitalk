#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv)
{
	int pid;
	int count;

	pid = getpid();
	printf("pid: %d\n", pid);

	count = 0;
	while(count < 1000)
	{
		sleep(1);
		count += 1;
	}
	return 0;
}