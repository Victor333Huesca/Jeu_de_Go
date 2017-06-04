#include"Arbre.h"
#include <iostream>
//Constructors

	Arbre::Arbre() : nbF(0)
	{
		gob=nullptr;
		fils=	new Goban[0];
		info=0;
		value=Etat::NOIR;
		filsA=nullptr;
		SABR= nullptr;
	}
	//par copie
	Arbre::Arbre(const Arbre & a)
{
	if (&a != this)
	{
		gob = new Goban(*a.getGob());
		nbF = a.getNbF();
		value = a.getValue();
		fils = new Goban[nbF];
		for (size_t i=0;i<nbF;i++)
		{
			fils[i]=a.fils[i];
		}
		info = a.getInfo();
		filsA =nullptr;
		SABR=nullptr;
	}
}

Arbre::Arbre(const Goban& G, Etat::VAL val)
{
	gob = new Goban(G);
	info=false;
	value=val;
	info=0;
	std::vector<Goban> f = gob->listFils(value);
	nbF= f.size();
	fils= new Goban[nbF];
	for (size_t i=0; i<f.size(); i++){
		fils[i]=f[i];
	}
	filsA= nullptr;
	SABR=nullptr;
	}

//Distructor
Arbre::~Arbre(){
	delete gob;
	if (filsA != nullptr) delete filsA;
	delete[] fils;
	delete[] SABR;
}
//Getters

Goban& Arbre::at(const size_t indice) const
{
	return fils[indice];
}

Goban* Arbre::getFils()
{
	return fils;
}

size_t Arbre::getNbF() const
{
	return this->nbF;
}

Goban* Arbre::getGob() const
{
	return gob;
}

bool Arbre::getInfo() const
{
	return this->info;
}

Etat::VAL Arbre::getValue() const
{
	return value;
}

Arbre* Arbre::getFilsA() const
{
	return filsA;
}

Arbre* Arbre::getSABR()
{
	return SABR;
}
Arbre& Arbre::getSABR(size_t i)
{
	return SABR[i];
}

//Setters

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
void Arbre::setFilsA(Goban& G, Etat::VAL val){
	delete filsA;
	filsA= new Arbre(G,val);
}

void Arbre::setSABR(Goban& G, Etat::VAL val, size_t i){
	std::cout<<"avant setSABR"<<std::endl;
	SABR[i]= Arbre(G,val);
	std::cout<<"après setSABR"<<std::endl;
}

Arbre& Arbre::operator[](const size_t i)const{
  return SABR[i];
}

//overloading methodes
Arbre Arbre::operator=(const Arbre a)
{
	std::cout << "Avant Arbre::operator=" << std::endl;
	if (this != &a)
	{
		delete gob;
		gob = new Goban(*a.gob);
		nbF = a.nbF;
		delete[] fils;
		fils= new Goban[nbF];
		for (size_t i=0; i< nbF; i++)
		{
			fils[i]= a.fils[i];
		}
		info = a.info;
		value = a.value;
		delete filsA;
		filsA= new Arbre(*a.getFilsA());
		SABR=nullptr;
		std::cout << "Apres Arbre::operator=" << std::endl;

	}
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

void Arbre::resetFils()
{
	std::vector<Goban> f=gob->listFils(value);
	nbF=f.size();
	delete[] fils;
	fils= new Goban[nbF];
	for (size_t i=0; i<nbF;i++)
	{
		fils[i]= f[i];
	}
	f.clear();
	f.resize(0);
}

void Arbre::elimFils(){
	delete[] fils;
	fils = new Goban [0];
}
void Arbre::defineSABR(){
	SABR = new Arbre[nbF];
	for (size_t i=0; i<nbF; i++){
		SABR[i]=Arbre();
	}
}
