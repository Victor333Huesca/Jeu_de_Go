#include"Arbre.h"
#include <iostream>
//Constructors

	Arbre::Arbre() : gob(), nbF(0)
	{
		fils=	std::vector<Goban>(0);
		info=0;
		value=Etat::NOIR;
		indice=0;
	}
	//par copie
	Arbre::Arbre(const Arbre & a)
{
	gob = new Goban(a.getGob());
	nbF = a.getNbF();
	value = a.getValue();
	fils = a.getFils();
	info = 0;
	indice = a.getIndice();
}

Arbre::Arbre(Goban& G, Etat::VAL val)
{
	std::cout << "Avant	 Arbre::Arbre()" << std::endl;

	gob = new Goban(G);
	info=false;
	value=val;
	fils= 	std::vector<Goban>(0);
	info=0;
	indice = 0;
	std::cout << "Apres Arbre::Arbre()" << std::endl;
}
//Distructor
Arbre::~Arbre(){
	delete gob;
}
//Getters

Goban Arbre::getFilsIndice(const size_t indice) const
{
	return fils[indice];
}

std::vector<Goban> Arbre::getFils() const
{
	return fils;
}

size_t Arbre::getNbF() const
{
	return this->nbF;
}

Goban Arbre::getGob() const
{
	return *gob;
}

bool Arbre::getInfo() const
{
	return this->info;
}

Etat::VAL Arbre::getValue() const
{
	return value;
}

size_t Arbre::getIndice() const
{
	return indice;
}

//Setters


void Arbre::setFils(const Goban& f)
{
	this->fils.push_back(f);
}

void Arbre::setNbF(size_t _nbF)
{
	this->nbF = _nbF;
}

void Arbre::setGob(const Goban& _gob)
{
	this->gob = new Goban(_gob);
}

void Arbre::setInfo(bool b)
{
	this->info = b;
}

void Arbre::setValue(Etat::VAL v)
{
	this->value = v;
}

void Arbre::setIndice(const size_t i)
{
	indice = i;
}

Goban& Arbre::operator[](unsigned short int i)
{
	return fils[i];
}

//overloading methodes
Arbre Arbre::operator=(Arbre a)
{
	std::cout << "Avant Arbre::operator=" << std::endl;

	if (this != &a)
	{
		gob = a.gob;
		nbF = a.nbF;
		fils.resize(a.fils.size());
		fils = a.fils;
		info = a.info;
		value = a.value;
	}

	std::cout << "Apres Arbre::operator=" << std::endl;

	return *this;
}

//Others methodes
void Arbre::effacerGoban(){
	delete gob;
}

void Arbre::afficher()
{
	std::cout <<"==============================="<<std::endl;
	std::cout << "============"<<value<<"=============" << std::endl;
	std::cout << this->getGob() << std::endl;
}

void Arbre::printArbo(const Arbre&)
{
	//Utiliser dotty ou latex ??
	std::cout << this->getGob() << std::endl;
}


std::ostream& operator<<(std::ostream &os, Arbre &n)
{
	n.afficher();
	return os;
}
