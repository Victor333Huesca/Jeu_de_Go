#ifndef ARBRE_H    
#define ARBRE_H
#include<iostream>
#include<vector>
#include”Goban.h”

class Arbre {
private:
	Goban gob; //Goban à l’instant T 
	bool info; //0 ou 1 si le coup apporte une victoire
	size_t nbF;    //Nombre de fils  
	Arbre * fils[]; //Tableau de fils
public:
	//Constructors
	Arbre();  //Constructeur par défaut
	Arbre(const Arbre&); //Constructeur par copie
	Arbre(const Goban&); //Constructeur 
	Arbre(const size_t); //Constructeur 
	Arbre(const size_t, const size_t);
	Arbre(const size_t, const size_t, Arbre * fils[]);

	//Destructors
	~Arbre(); //est un destructeur ;) ;)


			  //Getters
	Arbre* getFilsUnique(const size_t) const;
	size_t getNbF() const;
	Goban getGob() const;
	bool getInfo() const;


	//Setters
	void setFils(Arbre*, const size_t);
	void setNbF(size_t);
	void setgob(Goban);
	void setInfo(bool);

	//overloadings methodes
	Arbre * operator[](unsigned short int);
	bool operator<(const Arbre&);
	bool operator>(const Arbre&);
	bool operator<=(const Arbre&);
	bool operator>=(const Arbre&);
	bool operator==(const Arbre&);
	bool operator!=(const Arbre&);
	Arbre * operator=(Arbre&);
	Arbre * operator+(const Arbre&); //add two nodes 

	void afficher();
	//Others methods

	void printArbo(const Arbre&);
};

std::ostream& operator<<(std::ostream &os, Arbre &n);

#endif

