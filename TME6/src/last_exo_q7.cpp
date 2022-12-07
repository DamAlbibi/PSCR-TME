#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "rsleep.h"

// v1 without timer
/*
int wait_till_pid(pid_t pid) {

    int status = 0;
    while (wait(&status) != pid) {}
    return pid;
}
*/

// I don't see, how to without WNOHANG option and without signal, so I use waitpid nearly like wait (the problem is than wait suspend the program)
int wait_till_pid(pid_t pid, int sec) {

    int status = 0;
    clock_t endwait;
    endwait = clock() + sec * CLOCKS_PER_SEC ;

    while (waitpid(-1, &status, WNOHANG) != pid && clock() < endwait) {}

    if (clock() < endwait) return 0;
    return pid;
}

int main(int argc, char const *argv[])
{
    pid_t pid_s = fork();
    if (pid_s == 0) {
        sleep(2);
        std::cout << "vu" << std::endl;
    } else {
        std::cout << wait_till_pid(pid_s, 1) << std::endl;
        exit(0);
    }

    return 0;
}
