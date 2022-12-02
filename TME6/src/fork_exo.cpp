#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	int cpt_child = 0;
	int status = 0;
	int i;
	int j;
	std::cout << "main pid=" << getpid() << std::endl;

	for (i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		cpt_child = 0;
		std::cout << " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				j=0;
				cpt_child = 0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			} else {
				cpt_child++;
			}
		}
	}

	if (i<=N && j==N) {
		cpt_child++;
	}

	for (int i = 0; i < cpt_child; i++) {
		wait(&status);
	}
	
	return 0;
}
