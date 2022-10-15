#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

	void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
		
		//m.lock();
		if (deb < cred) {
			comptes[deb].getMutex().lock();
			comptes[cred].getMutex().lock();
		} else {
			comptes[cred].getMutex().lock();
			comptes[deb].getMutex().lock();
		}
		
		Compte & debiteur = comptes[deb];
		Compte & crediteur = comptes[cred];
		if (debiteur.debiter(val)) {
			crediteur.crediter(val);
		}

		comptes[deb].getMutex().unlock();
		comptes[cred].getMutex().unlock();
		//m.unlock();
		
	}
	size_t Banque::size() const {
		return comptes.size();
	}
	int Banque::getSolde(size_t i) const {
		return comptes[i].getSolde();
	}
	bool Banque::comptabiliser (int attendu) /*const*/ {

		int bilan = 0;
		int id = 0;
		//m.lock();
		for (auto & compte : comptes) {
			compte.getMutex().lock();
			if (compte.getSolde() < 0) {
				cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
			}
			bilan += compte.getSolde();
			id++;
		}
		for (auto & compte : comptes) {
			compte.getMutex().unlock();
		}
		//m.unlock();
		if (bilan != attendu) {
			cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
		}
		return bilan == attendu;
	}
}
