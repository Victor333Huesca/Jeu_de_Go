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
	DWORDLONG VirtualMemory = MS->ullTotalVirtual; // résultat en octets 
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

	return VirtualMemory - 20000000 < 0;
}


void IA::Tsumego(Arbre& A, Etat& cible)
{
	IA::loadNumber(A);
	IA::Tsumego_abr(A, cible);
}

void IA::Tsumego_abr(Arbre& A, Etat& cible)
{
	std::cout << "Nombre de noeuds restant : " << std::endl;
	std::cout << TOTAL_NODE_NUMBER - NODE_NUMBER << std::endl;

	if (warning())
	{
		std::cout << "Plus de mémoire disponible !" << std::endl;
		return;
	}

	NODE_NUMBER++;

	// Creer list de gobans des fils
	A.setNbF(A.getGob().listFils(A.getValue()).size());

	//std::cout << A.getNbF() << "  " << A.getInfo() << std::endl;
	
	std::cout << "Avant\n";
	std::vector<Goban> fils = A.getGob().listFils(A.getValue());
	std::cout << "Après" << std::endl;

	for (size_t i = 0; i < A.getNbF(); i++)
	{
		A.setFils(fils[i]);
	}
	
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
			A.setInfo(1);
		//std::cout<<A.getGob()<<std::endl;
		return;
	}


	size_t i = 0;

	// Creation des fils
	Arbre filsA;
	Etat::VAL val;
	while (i < A.getNbF() && A.getInfo() == 0)
	{
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;
		filsA = Arbre(A.getFils().at(i), val);
		if (filsA.getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal())
		{
			//cible en vie
			Tsumego_abr(filsA, cible);
		}
		else 
		{
			// Le coup a tué la cible
			A.setInfo(1);
			std::cout<< A.getGob() <<std::endl;
			return;
		}

		// S'areter si la réponse est deja trouvée (opti)
		if (filsA.getInfo() == 1) 
		{
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
