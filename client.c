#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: <PID> Message");
		return 1;
	}

	printf("Sending message to PID: %s\nMSG:%s\n", argv[1], argv[2]);
}