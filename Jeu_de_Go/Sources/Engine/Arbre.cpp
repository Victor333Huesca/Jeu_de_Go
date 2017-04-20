#include"Arbre.h"
#include <iostream>
//Constructors

	Arbre::Arbre() : gob(), nbF(0)
	{
		fils=	std::vector<Goban>(0);
		info=0;
		value=Etat::NOIR;
	}
	//par copie
	Arbre::Arbre(const Arbre & a)
{
	gob=a.getGob();
	nbF=a.getNbF();
	value=a.getValue();
	fils=a.getFils();
	info=0;
}

	Arbre::Arbre(Goban& G, Etat::VAL val) {
		gob = G;
		info=false;
		value=val;
		fils= 	std::vector<Goban>(0);
		info=0;
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


		void Arbre::setFils(Goban f)
		{
			this->fils.push_back(f);
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

	void Arbre::Tsumego(Etat& cible)
	{
		//creer list de gobans des fils
		nbF=gob.listFils(value).size();
		fils.resize(nbF);
		fils=gob.listFils(value);

		//CAS D'ARET
		if (nbF==0){
				bool enVie=0;
				if (gob.coord(cible.getX(),cible.getY()).getVal()==cible.getVal()){
					//cible en vie
					enVie=1;
				}
				if (value==cible.getVal() && enVie)
					info=1;
				else if (value!=cible.getVal() && !enVie)
					info=1;
					else
						info=0;
				//std::cout<<gob<<std::endl;
				return;
		}


		size_t i=0;
		//creation des fils
		Arbre filsA;
		Etat::VAL val;
		while (i < nbF && info==0){
		if (value == Etat::VAL::BLANC)
				val= Etat::VAL::NOIR;
		else
				val= Etat::VAL::BLANC;
		filsA=Arbre(fils[i], val);
		if (filsA.gob.coord(cible.getX(),cible.getY()).getVal()==cible.getVal()){
				//cible en vie
				filsA.Tsumego(cible);
			}
			else {
				//le coup a tué la cible
				info=1;
				//std::cout<<gob<<std::endl;
				return;
			}

			//s'areter si la réponse est deja trouvée (opti)
			if (filsA.info==1){}
			else {
				info=1;
				//std::cout<<gob<<std::endl;
				return;
			}
			i++;
		}
	}



	Goban Arbre::operator[](unsigned short int i)
	{
		return this->fils[i];
	}

	//overloading methodes
	Arbre Arbre::operator=(Arbre a) {
		if (this != &a) {
		  gob = a.gob;
			nbF = a.nbF;
			fils.resize(a.fils.size());
			fils = a.fils;
			info = a.info;
			value = a.value;
		}
		return *this;
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
