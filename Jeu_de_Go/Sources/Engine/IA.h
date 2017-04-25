#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

#include"Arbre.h"

class IA : public Arbre
{
public :
	// Tsumego
	static void Tsumego(Arbre&, Etat&);
	static bool Tsumego2(Arbre&, Etat&);

	// Infos methods
	static void loadNumber(Arbre&);
	static bool warning();

	// Tsumego methods
	//void Tsumego_naif(Arbre&, Etat&);
	static void Tsumego_abr(Arbre&, Etat&);
	static void Tsumego_abrCopieDeGarde(Arbre& A, Etat& cible);

private:
	static int TOTAL_NODE_NUMBER;
	static int NODE_NUMBER;
};
