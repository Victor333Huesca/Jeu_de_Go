#pragma once
#ifndef ARBRE_H
#define ARBRE_H
#include"../Jeu_de_Go/Sources/Engine/Goban.h"
#include<iostream>
#include<vector>


class Arbre {
private:
	Goban gob; 
	bool info;
	size_t nbF;
	Arbre * fils[];
public:
	//Constructors
	Arbre();
	Arbre(const Arbre&);
	Arbre(const Goban&);
	Arbre(const size_t);
	Arbre(const Goban&, const size_t);
	Arbre(const Goban&, const size_t, Arbre * fils[]);

	//Destructors
	~Arbre(); 

	//Getters
	Arbre * getFilsUnique(const size_t) const;
	size_t getNbF() const;
	Goban getGob() const;
	bool getInfo() const;

	//Setters
	void setFils(Arbre*, const size_t);
	void setNbF(size_t);
	void setGob(Goban);
	void setInfo(bool);

	//Others methods
	Arbre * operator[](unsigned short int);
	bool operator<(const Arbre&);
	bool operator>(const Arbre&);
	bool operator<=(const Arbre&);
	bool operator>=(const Arbre&);
	bool operator==(const Arbre&);
	bool operator!=(const Arbre&);
	bool operator=(const Arbre&);
	bool operator+(const Arbre&);

	void afficher();

	void printArbo(const Arbre&);
};

std::ostream& operator<<(std::ostream &os, Arbre &n);


#endif
