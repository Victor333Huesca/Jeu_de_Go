#ifndef ARBRE_H
#define ARBRE_H
#include"Goban.h"
#include<iostream>
#include<vector>

class Arbre {
private:
	Goban gob;
	Etat::VAL value;
	bool info;
	size_t nbF;
	Goban * fils;
public:
	//Constructors
	Arbre();
	Arbre(const Arbre&);
	Arbre(Goban&);
	Arbre(Goban&, Etat::VAL);
	Arbre(const bool);
	Arbre(Goban&, const size_t);
	Arbre(Goban& _gob, const size_t _nbF, Goban * _fils);

	//Destructors
	~Arbre();

	//Getters
	Goban getFilsIndice(const size_t) const;
	Goban* getFils() const;
	size_t getNbF() const;
	Goban getGob() const;
	bool getInfo() const;
	Etat::VAL getValue() const;

	//Setters
	void setFils(Goban, const size_t);
	void setNbF(size_t);
	void setGob(Goban);
	void setInfo(bool);
	void setValue(Etat::VAL);

	//overloading methodes
	Arbre operator=(Arbre);
	Arbre operator[](unsigned short int);

	//Others methods
	Arbre InitArbre(Goban&, Etat::VAL);
	void Tsumego(Arbre&, Etat);
	void afficher();
	void printArbo(const Arbre&);
};

std::ostream& operator<<(std::ostream &os, Arbre &n);


#endif
