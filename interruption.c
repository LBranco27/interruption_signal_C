//E função signal() permite o programa escolher como lidar com um sinal de interrupção
//do sistema operacional ou da função raise(). Como divisão por zero ou uma teclas
//ou combinação de teclas determinada pelo sistema operacional. (exemplo: SIGKILL de
//sistemas UNIX).
//
//signal() organiza um ISR (interrupt service routine) para reponder um "invocação"
//da interrupção especificada.
//
//O C padrão define 6 sinais:
//SIGABRT: "abort", abnormal termination.
//SIGFPE: floating point exception.
//SIGILL: "illegal", invalid instruction.
//SIGINT: "interrupt", interactive attention request sent to the program.
//SIGSEGV: "segmentation violation", invalid memory acess.
//SIGTERM: "terminate", termination request sent to the program.
//
//Porém, mais sinais podem ser especificados no header (signal.h). Em sistemas
//Unix e Unix-like (como Linux) possuem arquivos headers únicos e mais sinais.
//
//Dos sinais POSIX, temos, por exemplo o SIGKILL, utilizado para terminar imediatamente
//um processo.
//
//fontes:Wikipedia, IBM

#include <stdio.h>

//signal header
#include <signal.h>

//POSIX API
#include <unistd.h>

void clear_buffer(){
	int test;
	while ((test = getchar()) != '\n' && test != EOF) {
		//consume and discard characters until a newline or EOF is encountered
	}
}

void handle_sigint (int sig) {
	char key = 0;
	int no = 0;
	printf("\nYou have pressed signal number: %d\n\n", sig);
	while (no == 0) {
		printf("Are you sure you want to end the program? (Y/N): ");
		scanf("%c", &key);
		if (key == 'Y' || key == 'y') {

			//we raise the signal to terminate
			raise(SIGTERM);
		} else if (key == 'n' || key == 'N') {

			//leave loop
			no = 1;
			clear_buffer();
		}
	}
}

void print_message() {
	printf("--- C is good for the soul! ---\n");
}


int main () {

	//change the signal from the default function to handle_sigint
	signal(SIGINT, handle_sigint);
	puts("Press CTRL+C to exit");
	while (1){
		print_message();

		//wait 3 seconds
		sleep(1);
	}
	return 0;
}
