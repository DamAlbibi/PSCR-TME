#include <vector>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <chrono>
#include <thread>
#include "Banque.h"

// Question 2 : Crediter et debiter peuvent se faire en même temps
// ce qui peut poser des problèmes
// Question 4 : Juste de lock dans la fonction transfert pour créer
// un block

// Question 5 : ça bloque vu qu'on fait 2 fois lock sur le mutex
// j'utilise recursive_mutex, pour avoir un mutex avec un count 
// dessus, tant qu'il est pas à 0 ne se delock pas

// Question 6 : Probleme de deadlock, il pourrait avoir plusieur ordres de lock
// Dans transfert on met un ordre sur les locks

using namespace std;

void work(pr::Banque& bank) {
	for (int cpt = 0; cpt < 100; cpt++) {
		size_t nbCompte = bank.size();
		size_t i = rand() % nbCompte;
		size_t j = rand() % nbCompte;
		unsigned int m = (rand() % 100) + 1;
		int r = rand() % 21;

		bank.transfert(i, j, m);

		this_thread::sleep_for(chrono::milliseconds(r));
	}
}

const int NB_COMPTES = 10;
const int NB_THREAD = 5;
int main () {

	// TODO : creer des threads qui font ce qui est demandé

	vector<thread> threads;
	pr::Banque bank(NB_COMPTES, 10000);

	for (size_t i = 0; i < NB_THREAD; i++) {
		threads.emplace_back(work, std::ref(bank));
	}

	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	/*
	for (size_t i = 0; i < bank.size(); i++) {
		cout
	}
	*/
	return 0;
}
