#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <chrono>
#include "rsleep.h"




int wait_till_pid(pid_t pid, int sec) {
    std::cout << "prout";

    int status = 0;
    while (wait(&status) != pid) {
        sec--;
        if (sec <= 0) {
            return 0;
        }
    }
    return pid;
}

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid != 0) {
        std::cout << wait_till_pid(pid, 1) << std::endl;
    } else {
        while(true) {}
        exit(0);
    }

    return 0;
}
