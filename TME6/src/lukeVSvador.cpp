#include <iostream>
#include <unistd.h>
#include <signal.h>
#include "rsleep.h"
 
/*
    Question 6 : Le combat n'est plus equitable vu que Luke attend que son pere attaque avant d'attaquer a nouveau 
    (et donc se mettre en danger), Luke a donc l'avantage, il est sur de bloquer au moins 1 coup.
*/


int hp = 3;
bool is_vador;

void defense_reussis(int sig) {
    std::cout << "cout paré" << std::endl;
}

void loose1hp(int sig) {
    hp--;
    if (is_vador)  std::cout << "Vador ";
    else std::cout << "Luke ";
    if (hp != 0) std::cout << "il te restes " << hp << " hp" << std::endl;
    else std::cout << "est mort" << std::endl;
    if (hp <= 0) exit(1);
}

void attaque(pid_t adversaire) {
    signal(SIGINT, &loose1hp);
    if (kill(adversaire, SIGINT)){
        std::cout << "C'est gagne" << std::endl;
        exit(0);
    } 
    randsleep();
} 

void defense() {
    signal(SIGINT, SIG_IGN);
    randsleep();
}

void luke_defense() {

    sigset_t sigs;
    sigfillset(&sigs);
    sigdelset(&sigs, SIGINT);
    sigprocmask(SIG_BLOCK, &sigs, nullptr);

    struct sigaction sigact;
    sigact.sa_handler = &defense_reussis;
    sigact.sa_mask = sigs;
    sigact.sa_flags = SA_NOCLDWAIT;

    sigaction(SIGINT, &sigact, nullptr);
    
    randsleep();
    
    sigsuspend(&sigs);
}

void combat(pid_t adversaire) {
    while(true) {
        attaque(adversaire);
        defense();
    }
}

void combat_luke(pid_t adversaire) {
    while(true) {
        attaque(adversaire);
        luke_defense();
    }
}

int main() {
    pid_t cpid = fork();
    
    if (cpid != 0) {
        is_vador = true;
        signal(SIGINT, &loose1hp);
        randsleep();
        combat(cpid);
    } else {
        is_vador = false;
        signal(SIGINT, &loose1hp);
        randsleep();
        combat_luke(getppid());
    }
}