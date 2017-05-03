#include"IA.h"

int IA::TOTAL_NODE_NUMBER = 0;
int IA::NODE_NUMBER = 0;
bool IA::IS_TSUMEGO_RUNNING = false;

size_t factoriel(size_t n)
{
	size_t res=1;
	for (size_t i=1; i <= n;i++)
		res*=i;
	return res;
}

void IA::loadNumber(Arbre& A)
{
	int n = 0;
	for (short int i = 0; i < 19; i++)
		for (short int j = 0; j < 19; j++)
			if (A.getGob()->coord(i, j).getVal() == Etat::VIDE)
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
		if (!c[i + 8])
			c[i] = c[i + 8];
	}
	VirtualMemory = strtoul(c, NULL, 10);
#endif

	return VirtualMemory - 1000000000;
}

void IA::Tsumego(Arbre& A, Etat& cible)
{
	auto start = std::chrono::high_resolution_clock::now();
	auto finish = std::chrono::high_resolution_clock::now();
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);

	//std::cout<<"Dans le goban:"<<A.getGob()->coord(cible.getX(), cible.getY()).getVal()<<std::endl<<"La cible("<<cible.getX()<<","<<cible.getY()<<"):"<<cible.getVal()<<std::endl;
	loadNumber(A);
	IS_TSUMEGO_RUNNING = true;

	start = std::chrono::high_resolution_clock::now();
	size_t noeuds = Tsumego_abr(A, cible);
	finish = std::chrono::high_resolution_clock::now();
	microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);

	// -1 is the code return if the recursion has been aborted
	if (noeuds != (size_t)-1)
	{
		std::cout << "Temps du résolution du problème: " << (double)(microseconds.count()) << std::endl;
		std::cout << "Nombre de noeuds exploités: " << noeuds << std::endl;
		std::cout << "Nombre de noeuds total: " << factoriel(A.getNbF()) << std::endl;

		//AFFICHE RESULTAT DU TSUMEGO
		if ((A.getValue() == cible.getVal() && A.getInfo()) || (A.getValue() != cible.getVal() && !A.getInfo()))
			std::cout << "La cible a échapé!" << std::endl;
		else
			std::cout << "La cible a été capturé!" << std::endl;
		std::cout << "Une solution a ce problème est: " << std::endl;
		IA::Solution(A);
	}
	else
	{
		// recursion has been aborted
		std::cout << "Le Tsumego a été interompu !" << std::endl;
	}
	stop_tsumego();
}

/*
bool IA::Tsumego2(Arbre& A, Etat& cible)
{
	//loadNumber(A);
	//IA::Tsumego_abr(A, cible);
	if (false)//warning())
	{
		std::cout << "Plus de mémoire disponible !" << std::endl;
		return 0;
	}
	A.setNbF(A.getGob()->listFils(A.getValue()).size());
	std::cout << A.getNbF() << std::endl;
	std::vector<Goban> fils = A.getGob()->listFils(A.getValue());
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
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
*/

void IA::Tsumego_naif(Arbre& A, Etat& cible)//marche mais tros naif
{
	//std::cout << "Nombre de noeuds restant : " << TOTAL_NODE_NUMBER - NODE_NUMBER << std::endl;
	/*
	if (warning())
	{
		std::cout << "Plus de m�moire disponible !" << std::endl;
		return;
	}
	*/

	NODE_NUMBER++;

	// CAS D'ARET
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
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
			//std::cout<<"UNE FEUILLE"<<std::endl;
		return;
	}


	size_t i = 0;
	// Creation d'un fils
	Etat::VAL val;
	while (i < A.getNbF())
	{
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;

		//std::cout << "Avant filsA" << std::endl;
		A.setFilsA(A.at(i), val);
		//std::cout << "Apres filsA" << std::endl;

		if (A.getFilsA()->getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			Tsumego_naif(*A.getFilsA(), cible);
		}
		else
		{
			A.setInfo(1);
			return;
		}

		if (A.getFilsA()->getInfo() != 1)
		{
			A.setInfo(1);
			return;
		}

		//recalculer les fils

		i++;
	}
}

size_t IA::Tsumego_abr(Arbre& A, Etat& cible)//marche
{
	//std::cout << "Nombre de noeuds restant : " << TOTAL_NODE_NUMBER - NODE_NUMBER << std::endl;
	/*
	if (warning())
	{
		std::cout << "Plus de m�moire disponible !" << std::endl;
		return;
	}
	*/

	// Stop the recursion if we need for a reason or an other
	if (!IS_TSUMEGO_RUNNING)	return (size_t)-1;

	//recalculer les fils pour les cas ou l'arbre n'a pas de fils
	NODE_NUMBER++;
	size_t noeuds=1;

	// CAS D'ARET
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
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
			//std::cout<<"UNE FEUILLE"<<std::endl;
		return noeuds;
	}


	size_t i = 0;
	// Creation d'un fils
	Etat::VAL val;
	while (i < A.getNbF() && A.getInfo() == 0)
	{
		noeuds++;
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;

		///std::cout << "Avant filsA" << std::endl;
		A.setFilsA(A.at(i), val);
		//std::cout << "Apres filsA" << std::endl;

		if (A.getFilsA()->getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			noeuds += Tsumego_abr(*A.getFilsA(), cible);
		}
		else
		{
			A.setInfo(1);
			// Le coup a tu� la cible
			//std::cout<<"je passe par laaaaa"<<std::endl;
			//std::cout<<A[0].getGob()<<std::endl;
			//std::cout<<"Dans le goban:"<<A[0].getGob()->coord(cible.getX(), cible.getY()).getVal()<<std::endl<<"La cible("<<cible.getX()<<","<<cible.getY()<<"):"<<cible.getVal()<<std::endl;
			/*std::cout<< A.getGob() <<std::endl;
			std::cout<< A.getInfo() <<std::endl;
			*/
			return noeuds;
		}

		// S'areter si la r�ponse est deja trouv�e (opti)
		if (A.getFilsA()->getInfo() == 1)
		{
			//filsA est à 1 donc A est a 0, donc A cherche le fils suivant
			//recalculer fils
		}
		else
		{
			A.setInfo(1);
			/*std::cout<< A.getGob() <<std::endl;
			std::cout<< A.getInfo() <<std::endl;*/
			return noeuds;
		}
		i++;
	}

	// Just in case
	return (size_t)-1;
}

void IA::Solution (Arbre& A)
{
	std::cout<<*A.getGob()<<std::endl;
	if (A.getFilsA() != nullptr){
		Solution (*A.getFilsA());
	}
}

void IA::stop_tsumego()
{
	IS_TSUMEGO_RUNNING = false;
}

void IA::Tsumego_abrFils(Arbre& A, Etat& cible)//ne marche pas
{
	//std::cout << "Nombre de noeuds restant : " << TOTAL_NODE_NUMBER - NODE_NUMBER << std::endl;
	/*
	if (warning())
	{
		std::cout << "Plus de m�moire disponible !" << std::endl;
		return;
	}
	*/

	//recalculer les fils pour les cas ou l'arbre n'a pas de fils
	NODE_NUMBER++;

	//definir le tableau des sous-arbres
	A.defineSABR();

	// CAS D'ARET
	if (A.getNbF() == 0)
	{
		bool enVie =  0;
		if (A.getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
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
			//std::cout<<"UNE FEUILLE"<<std::endl;
		return;
	}


	size_t i = 0;
	// Creation d'un fils
	Etat::VAL val;
	while (i < A.getNbF() && A.getInfo() == 0)
	{
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;

		///std::cout << "Avant filsA" << std::endl;
		A.setSABR(A.at(i), val, i);
		//std::cout << "Apres filsA" << std::endl;

		if (A.getSABR(i).getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			Tsumego_abr(A.getSABR(i), cible);
		}
		else
		{
			A.setInfo(1);
			// Le coup a tu� la cible
			//std::cout<<"je passe par laaaaa"<<std::endl;
			//std::cout<<A[0].getGob()<<std::endl;
			//std::cout<<"Dans le goban:"<<A[0].getGob()->coord(cible.getX(), cible.getY()).getVal()<<std::endl<<"La cible("<<cible.getX()<<","<<cible.getY()<<"):"<<cible.getVal()<<std::endl;
			/*std::cout<< A.getGob() <<std::endl;
			std::cout<< A.getInfo() <<std::endl;
			*/
			return;
		}

		// S'areter si la r�ponse est deja trouv�e (opti)
		if (A.getSABR(1).getInfo() == 1)
		{
			//filsA est à 1 donc A est a 0, donc A cherche le fils suivant
			//recalculer fils
		}
		else
		{
			A.setInfo(1);
			/*std::cout<< A.getGob() <<std::endl;
			std::cout<< A.getInfo() <<std::endl;*/
			return;
		}
		i++;
	}
}

size_t IA::Tsumego_compresse(Arbre& A, const Etat& cible)
{
	// Stop the recursion if we need for a reason or an other
	if (!IS_TSUMEGO_RUNNING)	return (size_t)-1;

	// Recalculer les fils pour les cas ou l'arbre n'a pas de fils
	NODE_NUMBER++;
	size_t noeuds = 1;

	// CAS D'ARET
	if (A.getNbF() == 0)
	{
		bool enVie = 0;
		if (A.getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
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
		//std::cout<<"UNE FEUILLE"<<std::endl;
		return noeuds;
	}


	size_t i = 0;
	// Creation d'un fils
	Etat::VAL val;
	while (i < A.getNbF() && A.getInfo() == 0)
	{
		noeuds++;
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;

		///std::cout << "Avant filsA" << std::endl;
		A.setFilsA(A.at(i), val);
		//std::cout << "Apres filsA" << std::endl;

		if (A.getFilsA()->getGob()->coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			noeuds += Tsumego_compresse(*A.getFilsA(), cible);
		}
		else
		{
			return noeuds;
		}

		// S'areter si la r�ponse est deja trouv�e (opti)
		if (A.getFilsA()->getInfo() == 1)
		{
			//filsA est à 1 donc A est a 0, donc A cherche le fils suivant
			//recalculer fils
		}
		else
		{
			A.setInfo(1);
			/*std::cout<< A.getGob() <<std::endl;
			std::cout<< A.getInfo() <<std::endl;*/
			return noeuds;
		}
		i++;
	}

	// Just in case
	return (size_t)-1;
}