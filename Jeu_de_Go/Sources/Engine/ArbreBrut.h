#ifndef ArbreBrut_H
#define ArbreBrut_H
#include"Goban.h"
#include<iostream>
#include<vector>

class ArbreBrut {
private:
	Goban gob;
	Etat::VAL value;
	bool info;
	size_t nbF;
	Goban * fils;
public:
	//Constructors
	ArbreBrut();
	ArbreBrut(const ArbreBrut&);
	ArbreBrut(Goban&);
	ArbreBrut(Goban&, Etat::VAL);
	ArbreBrut(const bool);
	ArbreBrut(Goban&, const size_t);
	ArbreBrut(Goban& _gob, const size_t _nbF, Goban * _fils);

	//Destructors
	~ArbreBrut();

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
	ArbreBrut operator=(ArbreBrut);
	ArbreBrut operator[](unsigned short int);

	//Others methods
	ArbreBrut InitArbreBrut(Goban&, Etat::VAL);
	void Tsumego(ArbreBrut&, Etat);
	void afficher();
	void printArbo(const ArbreBrut&);
};

std::ostream& operator<<(std::ostream &os, ArbreBrut &n);


#endif
