#ifndef ARBRE_H
#define ARBRE_H
#include<iostream>
#include<vector>


class noeud {
private:
	size_t p;
	size_t nbF;
	noeud * fils[];
public:
	//Constructors
	noeud();
	noeud(const noeud&);
	noeud(const size_t);
	noeud(const size_t, const size_t);
	noeud(const size_t, const size_t, noeud **);

	//Destuctors
	~noeud();

	//Getters
	noeud* getFilsUnique(const size_t) const;
	size_t getNbF() const;
	size_t getP() const;

	//Setters
	void setFils(noeud*, const size_t);
	void setNbF(size_t);
	void setP(size_t);

	//overloadings methodes
	noeud * operator[](unsigned short int);
	bool operator<(const noeud&);
	bool operator>(const noeud&);
	bool operator<=(const noeud&);
	bool operator>=(const noeud&);
	bool operator==(const noeud&);
	bool operator!=(const noeud&);
	noeud * operator=(noeud&);
	noeud * operator+(const noeud&); //add two nodes 

	void afficher();
	//Others methods
	void printArbo(const noeud&);
};

std::ostream& operator<<(std::ostream &os, noeud &n);

#endif