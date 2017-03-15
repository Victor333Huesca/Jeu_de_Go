#pragma once
#ifndef ARBRE_H
#define ARBRE_H
#include"../Jeu_de_Go/Sources/Engine/Goban.h"
#include<iostream>
#include<vector>


class Arbre {
private:
	Goban gob; 
	Etat::VAL value;
	bool info;
	size_t nbF;
	Arbre * fils;
public:
	//Constructors
	Arbre();
	Arbre(const Arbre&);
	Arbre(Goban&);
	Arbre(Goban&, Etat::VAL);
	Arbre(const bool);
	Arbre(Goban&, const size_t);
	Arbre(Goban& _gob, const size_t _nbF, Arbre * _fils);

	//Destructors
	~Arbre(); 

	//Getters
	Arbre getFilsUnique(const size_t) const;
	size_t getNbF() const;
	Goban getGob() const;
	bool getInfo() const;
	Etat::VAL getValue() const;

	//Setters
	void setFils(Arbre, const size_t);
	void setNbF(size_t);
	void setGob(Goban);
	void setInfo(bool);
	void setValue(Etat::VAL);

	Arbre& InitArbre(Goban&, Etat::VAL);

	//overloading methodes
	Arbre operator=(Arbre);
	//Others methods
	Arbre operator[](unsigned short int);
	

	void afficher();

	void printArbo(const Arbre&);
};

std::ostream& operator<<(std::ostream &os, Arbre &n);


#endif
