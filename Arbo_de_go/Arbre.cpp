#include"Arbre.h"   //Police 10 sinon c’est trop grand !
#include <iostream> // la bite 
//Constructors       //oui

Arbre::Arbre() : gob(0), nbF(0)
{
	fils[0] = NULL;
}
//par copie
}Arbre::Arbre(const Arbre& n) : gob(n.getGob()), nbF(n.getNbF())
{
	for (size_t i = 0; i < nbF; i++)
	{
		fils[i] = n.getFilsUnique(i);
	}


	Arbre::Arbre(const size_t _gob) : gob(_gob), nbF(0)
	{
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = NULL;
		}
	}

	Arbre::Arbre(const size_t _gob, const size_t _nbF) :
		gob(_gob), nbF(_nbF)
	{
		for (size_t i = 0; i < nbF; i++)
		{
			fils[i] = NULL;
		}
	}

	Arbre::Arbre(const size_t _gob, const size_t _nbF, Arbre ** _fils) :
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
		for (size_t i = 0; i < this->nbF; i++)
		{
			if (fils[i] != NULL)
			{
				delete fils[i];
			}
		}
	}

	//Getters

	Arbre* Arbre::getFilsUnique(const size_t indice) const
	{
		return this->fils[indice];
	}

	size_t Arbre::getNbF() const
	{
		return this->nbF;
	}

	Goban Arbre::getGob() const
	{
		return this->gob;
	}

	//Setters

	void Arbre::setFils(Arbre * _fils, const size_t indice)
	{
		this->fils[indice] = _fils;
	}

	void Arbre::setNbF(size_t _nbF)
	{
		this->nbF = _nbF;
	}

	void Arbre::setGob(Goban _gob)
	{
		this->gob = _gob;
	}

	Arbre* Arbre::operator[](unsigned short int i)
	{
		return this->fils[i];
	}

	bool Arbre::operator<(const Arbre& n)
	{
		return (this->getGob() < n.getGob());
	}

	bool Arbre::operator>(const Arbre& n)
	{
		return (this->getGob() > n.getGob());
	}

	bool Arbre::operator<=(const Arbre& n)
	{
		return (this->getGob() <= n.getGob());
	}

	bool Arbre::operator>=(const Arbre& n)
	{
		return (this->getGob() >= n.getGob());
	}

	bool Arbre::operator==(const Arbre& n)
	{
		return (this->getGob() == n.getGob());
	}

	bool Arbre::operator!=(const Arbre& n)
	{
		return (this->getGob() != n.getGob());
	}

	Arbre * Arbre::operator=(Arbre& n)
	{
		if (this == &n)
		{
			return this;
		}
		else
		{
			Arbre * resultat(&n);
			return resultat;
		}
	}

	Arbre * Arbre::operator+(const Arbre& n1)
	{
		size_t a = n1.getGob();
		size_t b = this->getGob();
		size_t nbFa = n1.getNbF();
		size_t nbFb = this->getNbF();
		Arbre * filsa[nbFa + nbFb];
		Arbre * resultat;
		for (size_t i = 0; i < nbFa; i++)
		{
			filsa[i] = n1.getFilsUnique(i);
		}
		for (size_t i = nbFa; i < (nbFa + nbFb); i++)
		{
			filsa[i] = this->getFilsUnique(i - nbFa);
		}
		resultat->setGob(a + b); resultat->setNbF(nbFa + nbFb);
		for (size_t i = 0; i < (nbFa + nbFb); i++)
		{
			resultat->setFils(filsa[i], i);
		}
		return resultat;
	}

	//Others methods
	void Arbre::afficher()
	{
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


