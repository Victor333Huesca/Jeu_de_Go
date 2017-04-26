#include"IA.h"

int IA::TOTAL_NODE_NUMBER = 0;
int IA::NODE_NUMBER = 0;

void IA::loadNumber(Arbre& A)
{
	int n = 0;
	for (short int i = 0; i < 19; i++)
		for (short int j = 0; j < 19; j++)
			if (A.getGob().coord(i, j).getVal() == Etat::VIDE)
				n++;

	TOTAL_NODE_NUMBER = n * n;
}

bool IA::warning()
{
#ifdef _WIN32
	MEMORYSTATUSEX *MS = new MEMORYSTATUSEX;
	GlobalMemoryStatusEx(MS);
	DWORDLONG VirtualMemory = MS->ullTotalVirtual; // r�sultat en octets
	delete MS;
#else
	//Si on est sur linux
	long long VirtualMemory;
	char *c;
	*c = system("grep MemFree /proc/meminfo");
	for (short int i = 0; i + 8 < 64; i++)
	{
		if (c[i + 8] != NULL)
			c[i] = c[i + 8];
	}
	VirtualMemory = strtoul(c, NULL, 10);
#endif

	return VirtualMemory - 1000000000;
}

void IA::Tsumego(Arbre& A, Etat& cible)
{
	IA::loadNumber(A);
	IA::Tsumego_abr(A, cible);
}


bool IA::Tsumego2(Arbre& A, Etat& cible)
{
	//loadNumber(A);
	//IA::Tsumego_abr(A, cible);
	if (false)//warning())
	{
		std::cout << "Plus de mémoire disponible !" << std::endl;
		return 0;
	}
	A.setNbF(A.getGob().listFils(A.getValue()).size());
	std::cout << A.getNbF() << std::endl;
	std::vector<Goban> fils = A.getGob().listFils(A.getValue());
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			// Cible en vie
			enVie = 1;
		}
		if (A.getValue() == cible.getVal() && enVie)
		{
			A.setInfo(1);
			return 1;
		}
		else if (A.getValue() != cible.getVal() && !enVie)
		{
			A.setInfo(1);
			return 1;
		}
		else
		{
			A.setInfo(0);
			return 0;
		}
	}
	for (size_t i = 0; i < A.getNbF(); i++)
	{
		A.setFils(fils.at(i));

		if (fils[i].coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			if (A.getValue() == Etat::BLANC)
			{
				return !Tsumego2(Arbre(fils.at(i), Etat::NOIR), cible);
			}
			else
			{
				return !Tsumego2(Arbre(fils.at(i), Etat::BLANC), cible);
			}
		}
		else
		{
			std::cout << fils.at(i) << std::endl;
			A.setInfo(1);
			return 1;
		}
	}
	return 0;

}


void IA::Tsumego_naif(Arbre& A, Etat& cible)
{
	std::cout << "Nombre de noeuds restant : " << TOTAL_NODE_NUMBER - NODE_NUMBER << std::endl;
	/*
	if (warning())
	{
		std::cout << "Plus de m�moire disponible !" << std::endl;
		return;
	}
	*/

	NODE_NUMBER++;


	std::vector<Goban> fils = A.getGob().listFils(A.getValue());
	// Creer list de gobans des fils
	A.setNbF(fils.size());
	//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;
	A.getFils().resize(0);
	for (size_t i = 0; i < A.getNbF(); i++)
	{
		A.setFils(fils[i]);
	}
	//on vide le vector fils initial
	fils.resize(0);

	//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;

	// CAS D'ARET
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			// Cible en vie
			enVie = 1;
		}
		if (A.getValue() == cible.getVal() && enVie)
			A.setInfo(1);
		else if (A.getValue() != cible.getVal() && !enVie)
			A.setInfo(1);
		else
			A.setInfo(0);
		//std::cout<<A.getGob()<<std::endl;
		return;
	}

	size_t i = 0;
	uint8_t* gobcomp = A.getGob().compress();
	A.setIndice(0);
	// Creation d'un fils
	Arbre* filsA = nullptr;
	Etat::VAL val;

	while (A.getIndice() < A.getNbF())
	{
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;

		//std::cout << "Avant filsA" << std::endl;
		delete filsA;
		filsA = new Arbre(A.getFils().at(A.getIndice()), val);
		//std::cout << "Apres filsA" << std::endl;

		if (filsA->getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			//reinitialiser A.fils[] à 0 et garder le compresseur de A.goban en effacant le goban
			//lancer tsumego sur le fils
			A.getFils().resize(0);
			Tsumego_abr(*filsA, cible);
		}
		else
		{
			// Le coup a tu� la cible
			A.setInfo(1);
			//std::cout<< A.getGob() <<std::endl;
			return;
		}
		A.setIndice(A.getIndice() + 1);
	}
}

void IA::Tsumego_abr(Arbre& A, Etat& cible)
{
	std::cout << "Nombre de noeuds restant : " << TOTAL_NODE_NUMBER - NODE_NUMBER << std::endl;
	/*
	if (warning())
	{
		std::cout << "Plus de m�moire disponible !" << std::endl;
		return;
	}
	*/

	NODE_NUMBER++;


	std::vector<Goban> fils = A.getGob().listFils(A.getValue());
	// Creer list de gobans des fils
	A.setNbF(fils.size());
	//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;
	A.getFils().resize(0);
	for (size_t i = 0; i < A.getNbF(); i++)
	{
		A.setFils(fils[i]);
	}
	//on vide le vector fils initial
	fils.resize(0);

	//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;

	// CAS D'ARET
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			// Cible en vie
			enVie = 1;
		}
		if (A.getValue() == cible.getVal() && enVie)
			A.setInfo(1);
		else if (A.getValue() != cible.getVal() && !enVie)
			A.setInfo(1);
		else
			A.setInfo(0);
		//std::cout<<A.getGob()<<std::endl;
		return;
	}

	size_t i = 0;
	uint8_t* gobcomp = A.getGob().compress();
	A.setIndice(0);
	// Creation d'un fils
	Arbre* filsA = nullptr;
	Etat::VAL val;

	while (A.getIndice() < A.getNbF() && A.getInfo() == 0)
	{
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;

		//std::cout << "Avant filsA" << std::endl;
		delete filsA;
		filsA = new Arbre(A.getFils().at(A.getIndice()), val);
		//std::cout << "Apres filsA" << std::endl;

		if (filsA->getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			//reinitialiser A.fils[] à 0 et garder le compresseur de A.goban en effacant le goban
			//lancer tsumego sur le fils
			A.getFils().resize(0);
			Tsumego_abr(*filsA, cible);
		}
		else
		{
			// Le coup a tu� la cible
			A.setInfo(1);
			//std::cout<< A.getGob() <<std::endl;
			return;
		}

		// S'areter si la r�ponse est deja trouv�e (opti)
		if (filsA->getInfo() == 1)
		{
			//filsA est à 1 donc A est a 0, donc A cherche le fils suivant
			//on a besoin d'abord de decomprésser A et recalculer les fils
			A.getGob().uncompress(gobcomp,A.getValue());
			fils.resize(0);
			fils = A.getGob().listFils(A.getValue());
			// Creer list de gobans des fils
			A.setNbF(fils.size());
			//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;
			A.getFils().resize(0);
			for (size_t i = 0; i < A.getNbF(); i++)
			{
				A.setFils(fils[i]);
			}

		}
		else
		{
			A.setInfo(1);
			//std::cout<< A.getGob() <<std::endl;
			return;
		}
		A.setIndice(A.getIndice() + 1);
	}
}



void IA::Tsumego_abrCopieDeGarde(Arbre& A, Etat& cible)
{
	std::cout << "Nombre de noeuds restant : " << TOTAL_NODE_NUMBER - NODE_NUMBER << std::endl;
	/*
	if (warning())
	{
		std::cout << "Plus de m�moire disponible !" << std::endl;
		return;
	}
	*/

	NODE_NUMBER++;


	std::vector<Goban> fils = A.getGob().listFils(A.getValue());
	// Creer list de gobans des fils
	A.setNbF(fils.size());
	//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;
	A.getFils().resize(0);
	for (size_t i = 0; i < A.getNbF(); i++)
	{
		A.setFils(fils[i]);
	}

	//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;

	// CAS D'ARET
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			// Cible en vie
			enVie = 1;
		}
		if (A.getValue() == cible.getVal() && enVie)
			A.setInfo(1);
		else if (A.getValue() != cible.getVal() && !enVie)
			A.setInfo(1);
		else
			A.setInfo(0);
		//std::cout<<A.getGob()<<std::endl;
		return;
	}


	size_t i = 0;
	// Creation d'un fils
	Arbre* filsA = nullptr;
	Etat::VAL val;
	while (i < A.getNbF() && A.getInfo() == 0)
	{
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;

		//std::cout << "Avant filsA" << std::endl;
		delete filsA;
		filsA = new Arbre(A.getFils().at(i), val);
		//std::cout << "Apres filsA" << std::endl;

		if (filsA->getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			Tsumego_abr(*filsA, cible);
		}
		else
		{
			// Le coup a tu� la cible
			A.setInfo(1);
			//std::cout<< A.getGob() <<std::endl;
			return;
		}

		// S'areter si la r�ponse est deja trouv�e (opti)
		if (filsA->getInfo() == 1)
		{
			//filsA est à 1 donc A est a 0, donc A cherche le fils suivant
		}
		else
		{
			A.setInfo(1);
			//std::cout<< A.getGob() <<std::endl;
			return;
		}
		i++;
	}
}
