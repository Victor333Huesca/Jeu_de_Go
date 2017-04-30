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
	Goban* fils;
	Arbre* filsA;
	Arbre* SABR;
	size_t indice;
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
	Goban& at(const size_t) const;
	Goban* getFils();
	size_t getNbF() const;
	Goban* getGob() const;
	bool getInfo() const;
	Etat::VAL getValue() const;
	Arbre* getFilsA() const;
	Arbre* getSABR();
	Arbre& getSABR(size_t);
	//Setters
	void setNbF(size_t);
	void setGob(const Goban& g);
	void setInfo(bool);
	void setValue(Etat::VAL);
	void setFilsA(Goban& G, Etat::VAL val);
	void setSABR(Goban&, Etat::VAL, size_t);

	//overloading methodes
	Arbre operator=(const Arbre);
	Arbre& operator[](const size_t) const;

	//Others methodes
	void effacerGoban();
	void afficher();
	void printArbo(const Arbre&);
	void resetFils();
	void elimFils();
	void defineSABR();
};

std::ostream& operator<<(std::ostream &os, Arbre &n);


#endif
