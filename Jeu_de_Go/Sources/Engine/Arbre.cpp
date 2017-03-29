#include"Arbre.h"
#include <iostream>
//Constructors

	Arbre::Arbre() : gob(), nbF(0)
	{
		fils = NULL;
	}
	//par copie
	Arbre::Arbre(const Arbre & a): gob(a.getGob()), nbF(a.getNbF())
{
	fils = new Goban [nbF];
	for (size_t i = 0; i < nbF; i++)
	{
		Goban g=a.getFilsIndice(i);
		fils[i] = g;
	}
}

	Arbre::Arbre(Goban& G, Etat::VAL val) {
		gob = G;
		if (val == Etat::VAL::BLANC)
				value= Etat::VAL::NOIR;
			else
				value= Etat::VAL::BLANC;
	}

	//Destructors

	Arbre::~Arbre()
	{
		delete fils;
	}

	//Getters

	Goban Arbre::getFilsIndice(const size_t indice) const
	{
		return fils[indice];
	}

	Goban* Arbre::getFils() const
	{
		return fils;
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
		Arbre A(G,value);
		std::vector<Goban> listG = G.listFils(value);
		nbF = listG.size();
		fils = new Goban[nbF];
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = listG[i];
		}
		return A;
	}

	void Arbre::Tsumego(Arbre& A, Etat cible)
	{
		size_t i=0;
		Arbre filsA;
			while (i < A.nbF || A.info==0){
			filsA.InitArbre(A.fils[i], A.value);
			if (filsA.gob.coord(cible.getX(),cible.getY()).getVal()==cible.getVal()){
				// cible en vie
				if (A.value==cible.getVal()) A.info=1;
				else {
					size_t j=0;
					while(j< nbF || info== 0){
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
