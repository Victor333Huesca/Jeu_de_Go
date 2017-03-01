#include"arbre.h"

//Constructors

noeud::noeud(): p(0), nbF(0)
{
  fils[0] = NULL;
}

noeud::noeud(const noeud& n): p(n.getP()), nbF(n.getNbF())
{
  for(size_t i = 0; i < nbF; i++)
    {
      fils[i] = n.getFilsUnique(i);
      }
}

noeud::noeud(const size_t _p): p(_p), nbF(0)
{
  for(size_t i = 0; i < nbF; i++)
    {
      fils[i] = NULL;
    }
}

noeud::noeud(const size_t _p, const size_t _nbF):
  p(_p), nbF(_nbF)
{
  for(size_t i = 0; i < nbF; i++)
    {
      fils[i] = NULL;
    }
}

noeud::noeud(const size_t _p, const size_t _nbF, noeud ** _fils):
  p(_p), nbF(_nbF)
{
  for(size_t i = 0; i < nbF; i++)
    {
      fils[i] = _fils[i];
      }
}

//Destructors

noeud::~noeud()
{
  for(size_t i = 0; i < this->nbF; i++)
    {
      if(fils[i] != NULL)
	{
	  delete fils[i];
	}
    }
}

//Getters

noeud* noeud::getFilsUnique(const size_t indice) const
{
  return this->fils[indice];
}

size_t noeud::getNbF() const
{
  return this->nbF;
}

size_t noeud::getP() const
{
  return this->p;
}

//Setters

void noeud::setFils(noeud * _fils, const size_t indice)
{
  this->fils[indice] = _fils;
  }

void noeud::setNbF(size_t _nbF)
{
  this->nbF = _nbF;
} 

void noeud::setP(size_t _p)
{
  this->p = _p;
}

noeud* noeud::operator[](unsigned short int i)
{
  return this->fils[i];
}

bool noeud::operator<(const noeud& n)
{
  return (this->getP() < n.getP());
}

bool noeud::operator>(const noeud& n)
{
  return (this->getP() > n.getP());
}

bool noeud::operator<=(const noeud& n)
{
  return (this->getP() <= n.getP());
}

bool noeud::operator>=(const noeud& n)
{
  return (this->getP() >= n.getP());
}

bool noeud::operator==(const noeud& n)
{
  return (this->getP() == n.getP());
}

bool noeud::operator!=(const noeud& n)
{
  return (this->getP() != n.getP());
}

noeud * noeud::operator=(noeud& n)
{
  if(this==&n)
    {
      return this;
    }else
    {
      noeud * resultat(&n);
      return resultat;
     }
}

noeud * noeud::operator+(const noeud& n1)
{
  size_t a =  n1.getP();
  size_t b = this->getP();
  size_t nbFa = n1.getNbF();
  size_t nbFb = this->getNbF();
  noeud * filsa[nbFa+nbFb];
  noeud * resultat;
  for(size_t i = 0; i < nbFa; i++)
    {
      filsa[i] = n1.getFilsUnique(i);
    }
  for(size_t i = nbFa; i < (nbFa+nbFb); i++)
    {
      filsa[i] = this->getFilsUnique(i-nbFa);
    }
  resultat->setP(a+b); resultat->setNbF(nbFa+nbFb);
  for(size_t i = 0; i < (nbFa+nbFb); i++)
    {
      resultat->setFils(filsa[i], i);
    }
  return resultat;
}

//Others methods
void noeud::afficher()
{
  std::cout<<this->getP()<<std::endl;
}

std::ostream& operator<<(std::ostream &os, noeud &n)
{
  n.afficher();
  return os;
}

