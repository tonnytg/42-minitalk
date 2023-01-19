#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define MESSAGE_LENGTH 100


void read_message() {
	char message[MESSAGE_LENGTH];

	// lê a mensagem codificada do pipe
	read(pipefd[0], message, MESSAGE_LENGTH);

	// decodifica a mensagem
	for (int i = 0; i < MESSAGE_LENGTH; i++) {
		message[i] = message[i] ^ 0xFF;
	}

	printf("Mensagem recebida: %s\n", message);
}


int main() {
	pid_t pid;
	int pipefd[2];
	char message[MESSAGE_LENGTH];

	// cria um pipe para comunicação entre processos
	pipe(pipefd);

	// cria o processo filho
	pid = fork();

	if (pid == 0) {
		// processo filho
		close(pipefd[0]); // fecha o lado de leitura do pipe

		while (1) {
			printf("Digite a mensagem a ser enviada: ");
			scanf("%s", message);

			// codifica a mensagem em bitwise
			for (int i = 0; i < MESSAGE_LENGTH; i++) {
				message[i] = message[i] ^ 0xFF;
			}

			// escreve a mensagem codificada no pipe
			write(pipefd[1], message, MESSAGE_LENGTH);

			// envia o sinal SIGUSR1 para o processo pai
			kill(getppid(), SIGUSR1);
		}
	} else {
		// processo pai
		close(pipefd[1]); // fecha o lado de escrita do pipe

		while (1) {
			// aguarda pelo sinal SIGUSR1
			signal(SIGUSR1, read_message);
			pause();
		}
	}

	return 0;
}
