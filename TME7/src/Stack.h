#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>
#include <iostream>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	/*
		sem_wait: -- au compteur 
		sem_post: ++ au compteur 
	*/
	sem_t semFull;
	sem_t semEmpty;
	sem_t semMutex;
public :
	Stack () : sz(0) { 
		memset(tab,0,sizeof tab);
		sem_init(&semMutex, 1, 1);
		sem_init(&semFull, 1, STACKSIZE);
		sem_init(&semEmpty, 1, 0);
	}

	T pop () {
		// bloquer si vide
		sem_wait(&semEmpty);
		sem_wait(&semMutex);
		T toret = tab[--sz];
		sem_post(&semFull);
		sem_post(&semMutex);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&semFull);
		sem_wait(&semMutex);
		tab[sz++] = elt;
		sem_post(&semEmpty);
		sem_post(&semMutex);
	}
};

}
