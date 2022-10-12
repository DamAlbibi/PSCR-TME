#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <utility>
#include <unordered_map>
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

// Question 9: On pourrait construire une table de hachage qui associe l'age ou le prenom des personnes a une liste chaine de personne

int main () {

	using namespace std;
	using namespace std::chrono;

	unordered_map<std::string, int> u_map;

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

        auto it = u_map.find(word);
		if (it == u_map.end()) {
			u_map.insert(std::pair<std::string, int>(word, 1));
		} else {
			it->second++;
		}
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

	cout << "Found a total of " << u_map.find("war")->second << " war words." << endl;
	cout << "Found a total of " << u_map.find("peace")->second << " peace words." << endl;
	//cout << "Found a total of " << u_map.find("toto")->second << " toto words." << endl;

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


    // Part with the copy in a vector
    
    /*
	vector<pair<string, int>> v;
	v.reserve(20333);

	int counter = 0;

	for (auto it = u_map.begin(); it != u_map.end(); ++it) {
        v.emplace_back(std::pair<std::string,int> (it->first, it->second));
		counter++;
    }
	
	std::sort (v.begin(), v.end(), [] (const pair<string,int> occ1, const pair<string,int> occ2) {
		return occ1.second > occ2.second;
	});
    */


    // Part with the second unordered map

    unordered_map<int, forward_list<string>> u_map2;

    for (pair<string, int> p: u_map) {

        auto it = u_map2.find(p.second);
        forward_list<string> list;

		if (it == u_map2.end()) {
			u_map2.insert(pair<int, forward_list<string>>(p.second, list));
		}

        u_map2.find(p.second)->second.push_front(p.first);
    }


    cout << "mot apparaissant 35 fois : " << endl;
    
    for (string s: u_map2.find(35)->second) {
        cout << s << endl;
    }
    
    /*
    for (auto it = u_map2.find(2).begin(); it != u_map2.find(2).end(); ++it) {
		cout << *(it) << endl;
    }
    */


    return 0;
}


