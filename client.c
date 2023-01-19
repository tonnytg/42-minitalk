#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define MESSAGE_LENGTH 100

void send_message(char* message) {
	// aqui você pode enviar a mensagem codificada para o servidor
	// através de uma conexão de rede, serial, etc
	// e enviar o sinal SIGUSR1 para o processo pai no servidor
	// para indicar que a mensagem está pronta para ser lida
	kill(server_pid, SIGUSR1);
}

int main() {
	char message[MESSAGE_LENGTH];

	while (1) {
		printf("Digite a mensagem a ser enviada: ");
		scanf("%s", message);

		// codifica a mensagem em bitwise
		for (int i = 0; i < MESSAGE_LENGTH; i++) {
			message[i] = message[i] ^ 0xFF;
		}

		// envia a mensagem codificada para o servidor
		send_message(message);
	}

	return 0;
}


