#include"IA.h"

int TOTAL_NODE_NUMBER = 0;
int NODE_NUMBER = 0;

void IA::loadNumber(Arbre& A)
{
	int n = 0;
	for (short int i = 0; i < 19; i++)
	{
		for (short int j = 0; j < 19; j++)
		{
			if (A.getGob().coord(i, j).getVal() == Etat::VIDE)
				n++;
		}
	}
	TOTAL_NODE_NUMBER = n * n;
}

bool IA::warning()
{	
	unsigned long VirtualMemory;
	bool b = false;
	std::cout << "coucou" << std::endl;
	if (Win32)  //Si on est sur Windows
	{
		MEMORYSTATUSEX *MS = new MEMORYSTATUSEX;
		GlobalMemoryStatusEx(MS);
		VirtualMemory = MS->ullTotalVirtual; // résultat en octets 
		std::cout << VirtualMemory << std::endl;
		if (VirtualMemory - 2000000 < 0)
			b = true;
		delete MS;
	}
	else  //Si on est sur linux
	{
		char *c;
		*c = system("grep MemFree /proc/meminfo");
		for (short int i = 0; i + 8 < 64; i++)
		{
			if (c[i + 8] != NULL)
				c[i] = c[i + 8];
		}
		VirtualMemory = strtoul(c, NULL, 10);
	}
	
	return b;
}

void IA::Tsumego(Arbre& A, Etat& cible)
{
	if (warning())
	{
		std::cout << "Plus de mémoire disponible !" << std::endl;
		return;
	}
	NODE_NUMBER = NODE_NUMBER + 1;
	//creer list de gobans des fils
	A.setNbF(A.getGob().listFils(A.getValue()).size());
	for (short int petit_int_mignon = 0; petit_int_mignon < A.getNbF() - 1; petit_int_mignon++)
	{
		A.setFils(A.getGob().listFils(A.getValue()).at(petit_int_mignon), A.getNbF());
	}
	
	//CAS D'ARET
	if (A.getNbF() == 0) {
		bool enVie = 0;
		if (A.getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal()) {
			//cible en vie
			enVie = 1;
		}
		if (A.getValue() == cible.getVal() && enVie)
			A.setInfo(1);
		else if (A.getValue() != cible.getVal() && !enVie)
			A.setInfo(1);
		else
			A.setInfo(1);
		//std::cout<<gob<<std::endl;
		return;
	}


	size_t i = 0;
	//creation des fils
	Arbre filsA;
	Etat::VAL val;
	while (i < A.getNbF() && A.getInfo() == 0) {
		if (A.getValue() == Etat::VAL::BLANC)
			val = Etat::VAL::NOIR;
		else
			val = Etat::VAL::BLANC;
		filsA = Arbre(A.getFils().at(i), val);
		if (filsA.getGob().coord(cible.getX(), cible.getY()).getVal() == cible.getVal()) {
			//cible en vie
			Tsumego(filsA, cible);
		}
		else {
			//le coup a tué la cible
			A.setInfo(1);
			//std::cout<<gob<<std::endl;
			return;
		}

		//s'areter si la réponse est deja trouvée (opti)
		if (filsA.getInfo() == 1) {}
		else {
			A.setInfo(1);
			//std::cout<<gob<<std::endl;
			return;
		}
		i++;
	}
}
