#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <chrono>
#include "rsleep.h"

bool is_timer_finish = false;

void child_death(int sig) {
    
}
 
void end_of_timer(int sig) {
    std::cout << pid_cible << std::endl;
    is_timer_finish = true;
}

int wait_till_pid(pid_t pid, int sec) {

    int status = 0;

    alarm(sec);

    signal(SIGALRM, &end_of_timer);

    wait(&status);

    //while (!is_timer_finish && wait(&status) != pid) {}
    std::cout << "pataat" << std::endl;
    if (is_timer_finish) return 0;
    return pid;
}

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid != 0) {
        std::cout << wait_till_pid(pid, 2) << std::endl;
    } else {
        signal(SIGCHLD, &child_death);
        signal(SIGALRM, &child_death);
        while(true) {}
        exit(0);
    }

    return 0;
}
