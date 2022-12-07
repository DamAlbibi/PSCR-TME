#include "Stack.h"
#include "chat_common.h"
#include <iostream>

using namespace std;
using namespace pr;

Stack<message>* m_send;
Stack<message>* m_receive;

char buf1[10];
char buf2[10];


void end(int sig) {

	munmap(m_send, sizeof(Stack<message>));
	shm_unlink(buf1);

    munmap(m_receive, sizeof(Stack<message>));
	shm_unlink(buf2);

    // end the client

}

void send(Stack<message>* s_send) {
	message mes;
	mes.type = 2;
	char c[10];
	while (cin.get(c, 10)) {
		strcpy(mes.content, c);
		s_send->push(mes);
	}
}


void receive(Stack<message>* s_receive) {
	signal(SIGINT, end);
    while (true) {
		message mes = s_receive->pop();
		std::cout << mes.content << flush;
	}
}

int main(int argc, char* argv[]) {

    int fd1, fd2; // file descriptor

    if (argc <= 2) {
        perror("Not enought argument");
        return 1;
    }  

	strcpy(buf1, "/");
	strcat(buf1, argv[1]);

	strcpy(buf2, "/");
	strcat(buf2, argv[2]);
	
	if((fd1 = shm_open(buf1, O_RDWR | O_CREAT | O_EXCL, 0600)) == - 1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(fd1, sizeof(Stack<message>)) == -1) {
		perror("ftruncate");
		exit(2);
	}

	if ((m_receive = (Stack<message>*) mmap(NULL, sizeof(Stack<message>), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(3);
	}


    if((fd2 = shm_open(buf2, O_RDWR | O_CREAT | O_EXCL, 0600)) == - 1) {
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(fd2, sizeof(Stack<message>*)) == -1) {
		perror("ftruncate");
		exit(2);
	}

	if ((m_send = (Stack<message>*) mmap(NULL, sizeof(Stack<message>), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(3);
	}

	// Send the id of client to the server

	message mes;
	mes.type = 1;
	strcpy(mes.content, buf1);
	m_send->push(mes);
    
	pid_t pp = fork();
	if (pp==0) {
		send(m_send);
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		receive(m_receive);
		return 0;
	}

    wait(0);
	wait(0);

    return 0;
}