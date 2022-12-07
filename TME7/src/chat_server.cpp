#include "chat_common.h"
#include "Stack.h"
#include "iostream"

#define SIZE 100

using namespace std;
using namespace pr;

Stack<message>* sp;
char buf[10];


void end(int sig) {
    munmap(sp, sizeof(Stack<message>));
	shm_unlink(buf);
}

void server(Stack<message>* stack) {
	char* ids[TAILLE_MESS];
	while (true) {
		message mes = stack->pop();
		// Connexion
		if (mes.type == 1) {
			std::cout << "1" << std::endl;
		}

		// Diffusion message 
		if (mes.type == 2) {
			std::cout << "2" << std::endl;
		}

		// Disconnect 
		if (mes.type == 3) {
			std::cout << "3" << std::endl;
		}
		std::cout << mes.content << flush;
	}
}

int main(int argc, char* argv[]) {

    int fd; // file descriptor

    if (argc == 1) {
        perror("Not enought argument");
        return 1;
    }  

	strcpy(buf, "/");
	strcat(buf, argv[1]);

	
	if((fd = shm_open(buf, O_RDWR | O_CREAT | O_EXCL, 0600)) == - 1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(fd, sizeof(Stack<message>)) == -1) {
		perror("ftruncate");
		exit(2);
	}

	if ((sp = (Stack<message>*) mmap(NULL, sizeof(Stack<message>), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(3);
	}

	pid_t pp = fork();
	if (pp==0) {
		server(sp);
		return 0;
	} else {
		signal(SIGINT, &end);
	}

	wait(0);

    return 0;
}