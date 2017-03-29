#include"ArbreBrut.h"
#include <iostream>
//Constructors

	ArbreBrut::ArbreBrut() : gob(), nbF(0)
	{
		fils = NULL;
	}
	//par copie
	ArbreBrut::ArbreBrut(const ArbreBrut & a): gob(a.getGob()), nbF(a.getNbF())
{
	fils = new Goban [nbF];
	for (size_t i = 0; i < nbF; i++)
	{
		Goban g=a.getFilsIndice(i);
		fils[i] = g;
	}
}

	ArbreBrut::ArbreBrut(Goban& G, Etat::VAL val) {
		gob = G;
		if (val == Etat::VAL::BLANC)
				value= Etat::VAL::NOIR;
			else
				value= Etat::VAL::BLANC;
	}

	//Destructors

	ArbreBrut::~ArbreBrut()
	{
		delete fils;
	}

	//Getters

	Goban ArbreBrut::getFilsIndice(const size_t indice) const
	{
		return fils[indice];
	}

	Goban* ArbreBrut::getFils() const
	{
		return fils;
	}

	size_t ArbreBrut::getNbF() const
	{
		return this->nbF;
	}

	Goban ArbreBrut::getGob() const
	{
		return this->gob;
	}

	bool ArbreBrut::getInfo() const
	{
		return this->info;
	}

	Etat::VAL ArbreBrut::getValue() const
	{
		return value;
	}

	//Setters


		void ArbreBrut::setFils(Goban f, const size_t i)
		{
			this->fils[i] = f;
		}

		void ArbreBrut::setNbF(size_t _nbF)
	{
		this->nbF = _nbF;
	}

	void ArbreBrut::setGob(Goban _gob)
	{
		this->gob = _gob;
	}

	void ArbreBrut::setInfo(bool b)
	{
		this->info = b;
	}

	void ArbreBrut::setValue(Etat::VAL v)
	{
		this->value = v;
	}

	ArbreBrut ArbreBrut::InitArbreBrut(Goban& G, Etat::VAL value)
	{
		ArbreBrut A(G,value);
		std::vector<Goban> listG = G.listFils(value);
		nbF = listG.size();
		fils = new Goban[nbF];
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = listG[i];
		}
		return A;
	}

	void ArbreBrut::Tsumego(ArbreBrut& A, Etat cible)
	{
		size_t i=0;
		ArbreBrut filsA;
			while (i < A.nbF){
			filsA.InitArbreBrut(A.fils[i], A.value);
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


	ArbreBrut ArbreBrut::operator[](unsigned short int i)
	{
		return this->fils[i];
	}

	//overloading methodes
	ArbreBrut ArbreBrut::operator=(ArbreBrut a) {
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
	void ArbreBrut::afficher()
	{
		std::cout <<"==============================="<<std::endl;
		std::cout << "============"<<value<<"=============" << std::endl;
		std::cout << this->getGob() << std::endl;
	}

	void ArbreBrut::printArbo(const ArbreBrut&)
	{
		//Utiliser dotty ou latex ??
		std::cout << this->getGob() << std::endl;
	}


	std::ostream& operator<<(std::ostream &os, ArbreBrut &n)
	{
		n.afficher();
		return os;
	}
