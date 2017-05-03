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
	//static bool Tsumego2(Arbre&, Etat&);

	// Infos methods
	static void loadNumber(Arbre&);
	static bool warning();

	// Tsumego methods
	static void Tsumego_naif(Arbre&, Etat&);
	static void Tsumego_abrFils(Arbre&, Etat&);
	static size_t Tsumego_abr(Arbre&, Etat&);
	static void Solution (Arbre& A);
	static void stop_tsumego();

private:
	static int TOTAL_NODE_NUMBER;
	static int NODE_NUMBER;
	static bool IS_TSUMEGO_RUNNING;
};
