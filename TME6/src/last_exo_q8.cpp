#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <chrono>
#include "rsleep.h"

bool is_timer_finish = false;
bool is_dead = false;

void child_death(int sig) {
    is_dead = true;
}
 

void end_of_timer(int sig) {
    is_timer_finish = true;
}


int wait_till_pid(pid_t pid, int sec) {

    std::cout << pid << std::endl;

    alarm(sec);

    signal(SIGALRM, &end_of_timer);
    signal(SIGCHLD, &child_death);

    pid_t wait_value;
    int status = 0;

    while (!is_timer_finish && wait_value != pid) {
        if (is_dead) {
            wait_value = wait(&status);
            is_dead = false;
        }
        if (wait_value == -1) {
            perror("wait main ");
            return -1;
        }
    }

    // We discard the timer
    alarm(0);

    if (is_timer_finish) {
        return 0;
    }
    return pid;
}

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid == 0) {
        sleep(2);
        std::cout << "vu" << std::endl;
    } else {
        std::cout << wait_till_pid(pid, 1) << std::endl;
        exit(0);
    }

    return 0;
}
