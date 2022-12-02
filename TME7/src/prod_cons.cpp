#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>


using namespace std;
using namespace pr;

// Voir avec le prof pour la futex error, je pense que c'est en rapport avec le semaphore qui attend alors que l'objet n'existe plus


Stack<char>* sp;

void end(int sig) {
	munmap(sp, sizeof(Stack<char>));
	shm_unlink("/monStack");

	// flag with sigaction to not have to put wait in a handler
	//delete sp;
}

void producteur (Stack<char> * stack) {
	char c;
	while (cin.get(c)) {
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	signal(SIGINT, end);
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {

	int fd; // file descriptor

	
	if((fd = shm_open("/monStack", O_RDWR | O_CREAT | O_EXCL, 0600)) == - 1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(fd, sizeof(Stack<char>)) == -1) {
		perror("ftruncate");
		exit(2);
	}

	if ((sp = (Stack<char>*) mmap(NULL, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(3);
	}

	*sp = Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		producteur(sp);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(sp);
		return 0;
	}

	
	wait(0);
	wait(0);
	
	return 0;
}

