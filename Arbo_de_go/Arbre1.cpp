#include"Arbre.h"
#include <iostream>
//Constructors

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

	Arbre::Arbre(Goban& _gob, const size_t _nbF, Goban * _fils) :
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

	Goban Arbre::getFilsUnique(const size_t indice) const
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


		void Arbre::setFils(Goban f, const size_t i)
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

	Arbre Arbre::InitArbre(Goban& G, Etat::VAL value)
	{
		Arbre A(G);
		std::vector<Goban> listG = G.listFils(value);
		if (value == Etat::VAL::BLANC)
			A.setValue( Etat::VAL::NOIR);
		else
			A.setValue(Etat::VAL::BLANC);
		nbF = listG.size();
		fils = new Goban[nbF];
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = listG[i];
		}
		return A;
	}

	void Arbre::Tsumego(Arbre& A, Etat::VAL value,Etat cible)
	{
		int i=0;
		Arbre filsA;
			while (i < A.nbF || A.info!=0){
			filsA.InitArbre(A.fils[i]);
			if (filsA.gob.coord(cible.getx(),cible.gety()).getValue()==cile.getValue()){
				// cible en vie
				if (value==cible.getVal()) A.info=1;
				else {
					int j=0;
					while(j< nbF || info != 1){
						filsA.Tsumego(filsA.fils[j],inverse(value),cible);
						if(filsA.fils[j].info==1) A.info=0;
						else A.info=1;
						j++;
					}
				}
			}
			i++;
		}
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
