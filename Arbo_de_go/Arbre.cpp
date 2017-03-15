#include"Arbre.h"   //Police 10 sinon c’est trop grand !
#include <iostream> // la bite 
//Constructors       //oui

	Arbre::Arbre() : gob(), nbF(0)
	{
		fils[0] = NULL;
	}
	//par copie
	Arbre::Arbre(const Arbre & a): gob(a.getGob()), nbF(a.getNbF())
{
	for (size_t i = 0; i < nbF; i++)
	{
		fils[i] = a.getFilsUnique(i);
	}
}
	Arbre::Arbre(Goban& _gob) :
		gob(_gob), nbF(0)
	{
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = NULL;
		}
	}

	Arbre::Arbre(Goban& G, Etat::VAL val) {
		gob = G;
		value = val;
		nbF = 0;
	}

	Arbre::Arbre(const bool b): gob(), nbF(0)
	{
		this->setInfo(b);
	}

	Arbre::Arbre(Goban& _gob, const size_t _nbF) :
		gob(_gob), nbF(_nbF)
	{
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = NULL;
		}
	}

	Arbre::Arbre(Goban& _gob, const size_t _nbF, Arbre * _fils) :
		gob(_gob), nbF(_nbF)
	{
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = _fils[i];
		}
	}

	//Destructors

	Arbre::~Arbre()
	{
		
		delete fils;
			
	}

	//Getters

	Arbre Arbre::getFilsUnique(const size_t indice) const
	{
		return fils[indice];
	}

	size_t Arbre::getNbF() const
	{
		return this->nbF;
	}

	Goban Arbre::getGob() const
	{
		return this->gob;
	}

	bool Arbre::getInfo() const
	{
		return this->info;
	}

	Etat::VAL Arbre::getValue() const
	{
		return value;
	}

	//Setters

	
		void Arbre::setFils(Arbre f, const size_t i)
		{
			this->fils[i] = f;
		}

		void Arbre::setNbF(size_t _nbF)
	{
		this->nbF = _nbF;
	}

	void Arbre::setGob(Goban _gob)
	{
		this->gob = _gob;
	}

	void Arbre::setInfo(bool b)
	{
		this->info = b;
	}

	void Arbre::setValue(Etat::VAL v)
	{
		this->value = v;
	}

	Arbre& Arbre::InitArbre(Goban& G, Etat::VAL value)
	{
		Arbre A(G);
		std::vector<Goban> listG = G.listFils(value);
		if (value == Etat::VAL::BLANC)
			value = Etat::VAL::NOIR;
		else
			value = Etat::VAL::BLANC;
		nbF = listG.size();
		fils = new Arbre[nbF];
		for (size_t i = 0; i < nbF; i++)
		{
			Arbre f(listG[i],value);
			fils[i] = f;
		}
		return A;
	}

	Arbre Arbre::operator[](unsigned short int i)
	{
		return this->fils[i];
	}

	//overloading methodes
	Arbre Arbre::operator=(Arbre a) {
		if (this != &a) {
		    gob = a.gob;
			nbF = a.nbF;
			fils = a.fils;
			info = a.info;
			value = a.value;
		}
		return this;
	}

	//Others methods
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


