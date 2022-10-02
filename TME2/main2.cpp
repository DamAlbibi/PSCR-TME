#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include "HashMap.hh"

// Question 1: Il compte le nombre de mot dans le fichier texte WarAndPeace.txt qui est donc compose de 566193 mots
// Question 2: Il compte avec 20333 mots differents en 10405 ms avec le vector
// Question 3: Il compte 298 war words et 114 peace words, ce bouquin c'est plus la guerre que la paix quoi. 0 toto aussi
// Question 4: Du O(n2), pas ouf la quadratique. On aurait pu utiliser une table de hachage (map en c++)

int main () {

	using namespace std;
	using namespace std::chrono;

	pr::HashMap<std::string, int> hashMap = pr::HashMap<std::string, int>(20333);

	ifstream input = ifstream("WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;

		if (hashMap.get(word) == nullptr) {
			hashMap.put(word, 1);
		} else {
			hashMap.put(word, ++(*(hashMap.get(word))));
		}
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

	cout << "Found a total of " << *(hashMap.get(std::string ("war"))) << " war words." << endl;
	cout << "Found a total of " << *(hashMap.get(std::string ("peace"))) << " peace words." << endl;
	cout << "Found a total of " << hashMap.get(std::string ("toto")) << " peace words." << endl;

    return 0;
}


