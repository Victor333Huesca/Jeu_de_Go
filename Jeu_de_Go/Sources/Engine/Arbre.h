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
	std::vector<Arbre> Afils;
	size_t indiceGagnant;
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
	std::vector<Arbre> getAFils() const;
	Arbre getAFilsIndice(const size_t) const;
	Goban getFilsIndice(const size_t) const;
	std::vector<Goban> getFils() const;
	size_t getNbF() const;
	Goban getGob() const;
	bool getInfo() const;
	Etat::VAL getValue() const;
	size_t getIndice() const;

	//Setters
	void setAFils(Arbre);
	void setFils(const Goban& g);
	void setNbF(size_t);
	void setGob(const Goban& g);
	void setInfo(bool);
	void setValue(Etat::VAL);
	void setIndice(const size_t);

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
