#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

	void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
		
		
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
		
	}
	size_t Banque::size() const {
		return comptes.size();
	}
	bool Banque::comptabiliser (int attendu) const {
		int bilan = 0;
		int id = 0;
		for (const auto & compte : comptes) {
			if (compte.getSolde() < 0) {
				cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
			}
			bilan += compte.getSolde();
			id++;
		}
		if (bilan != attendu) {
			cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
		}
		return bilan == attendu;
	}
}
