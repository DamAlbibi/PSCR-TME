#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        exit(4);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    // Version with the modification of argv 
    /*
    int index;
    for (int i = 0; i < argc; i++) {
        if (argv[i] == "|") {
            index = i;
            argv[i] = nullptr;
        }
    }
    */

    // Version with allocation
    int index;
    for (int i = 0; i < argc; i++) {
        if (argv[i] == "|") {
            index = i;
        }
    }

    char** arg1 = new char*[index-1];
    for (int i = 1; i < index; i++) {
        arg1[i] = argv[i];
    }

    char** arg2 = new char*[argc-index];
    for (int i = 1; i < index; i++) {
        arg2[i] = argv[i];
    }
    

    pid_t son1, son2;
    son1 = fork();

    if (son1 == -1) {
        perror("fork");
        exit(2);
    }

    if (fork() == 0) {
        // First function
        // Here I write in the pipe 
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        if (execv(arg1[0], arg1) == -1) {
            perror("execv");
            exit(3);
        }
    }

    son2 = fork();

    if (son2 == -1) {
        perror("fork");
        exit(2);
    }

    if (fork() == 0) {
        // Second function
        // Here I read
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        if (execv(arg2[0], arg2) == -1) {
            perror("execv");
            exit(3);
        }
    }
}
