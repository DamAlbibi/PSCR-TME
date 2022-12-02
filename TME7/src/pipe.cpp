#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

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
    std::string s = std::string("|");

    int index = 0;
    for (int i = 0; i < argc; i++) {
        if (argv[i] == s) {
            index = i;
        }
    }
    
    char** arg1 = new char*[index];
    int i = 1;
    for (int j = 0; i < index;j++) {
        arg1[j] = argv[i];
        i++;
    }

    i = index + 1;
    char** arg2 = new char*[argc-index-1];
    for (int j = 0; i < argc; j++) {
        arg2[j] = argv[i];
        i++;
    }
    
    //std::cout << arg2[2] << std::endl;


    pid_t son1, son2;
    son1 = fork();

    if (son1 == -1) {
        perror("fork");
        exit(2);
    }

    if (son1 == 0) {
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

    if (son2 == 0) {
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

    // Je comprends pas pourquoi si j'attend le 2eme fils ca fait une boucle infini
    
    wait(0);
   
    return 0;
}
