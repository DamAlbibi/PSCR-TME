#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <utility>
#include "HashMap.hh"
#include "generique.hh"

// Question 1: Il compte le nombre de mot dans le fichier texte WarAndPeace.txt qui est donc compose de 566193 mots
// Question 2: Il compte avec 20333 mots differents en 10405 ms avec le vector
// Question 3: Il compte 298 war words et 114 peace words, ce bouquin c'est plus la guerre que la paix quoi. 0 toto aussi
// Question 4: Du O(n2), pas ouf la quadratique. On aurait pu utiliser une table de hachage (map en c++)
// Question 5 et 6 : faite 
// Question 7 : faite cependant comment utiliser le constructeur par copie range, vu que ma hashMap est un vector avec des forward 
// list et non directement des couples meme si de maniere implicite il me transforme mes Entry<string, int> en pair<string,int>, 
// il pourra le faire pour une 1 seul liste nan ? 

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
	cout << "Found a total of " << hashMap.get(std::string ("toto")) << " toto words." << endl;

	// Comment utiliser le constructeur par copie range, vu que ma hashMap est un vector avec des forward list et non directement des couples 
	// meme si de maniere implicite il me transforme mes Entry<string, int> en pair<string,int>, il pourra le faire pour une 1 seul liste nan ? 

	/*
	std::vector<pair<string, int>> vector = hashMap.getCopy();

	std::sort(vector.begin(), vector.end(), [] (const pair<string,int> occ1, const pair<string,int> occ2) {
		return occ1.second > occ2.second;
	});

	for (pair<string, int> p: vector) {
		cout << p.first << " = " << p.second << endl;
	}
	*/

	// It slow, strangely slow, I have made a mistake in my hashmap iterator

	vector<pair<string, int>> v;
	v.reserve(20333);

	int counter = 0;

	for (auto it = hashMap.begin(); it != hashMap.end(); ++it) {
		cout << counter << " : " << (*it).getEntry() << endl;
        v.emplace_back(make_pair((*it).getEntry(), *((*it).getValue())));
		counter++;
    }
	
	std::sort (v.begin(), v.end(), [] (const pair<string,int> occ1, const pair<string,int> occ2) {
		return occ1.second > occ2.second;
	});

    return 0;
}


