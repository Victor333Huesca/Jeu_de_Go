#ifndef ARBRE_H
#define ARBRE_H
#include"Goban.h"
#include<iostream>
#include<vector>

class Arbre {
private:
	Goban* gob;
	Etat::VAL value;
	bool info;
	size_t nbF;
	std::vector<Goban> fils;
	size_t indiceGagnant;

public:
	//Constructors
	Arbre();
	Arbre(const Arbre&);
	Arbre(Goban&, Etat::VAL);
	Arbre(Goban&, const size_t);
	Arbre(Goban& _gob, const size_t _nbF, Goban * _fils);
	//Sistructor
	~Arbre();

	//Getters
	Goban getFilsIndice(const size_t) const;
	std::vector<Goban> getFils() const;
	size_t getNbF() const;
	Goban getGob() const;
	bool getInfo() const;
	Etat::VAL getValue() const;

	//Setters
	void setFils(const Goban& g);
	void setNbF(size_t);
	void setGob(const Goban& g);
	void setInfo(bool);
	void setValue(Etat::VAL);

	//overloading methodes
	Arbre operator=(Arbre);
	Goban& operator[](unsigned short int);

	//Others methodes
	void effacerGoban();  
	void afficher();
	void printArbo(const Arbre&);
};

std::ostream& operator<<(std::ostream &os, Arbre &n);


#endif
