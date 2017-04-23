#pragma once
#include"Arbre.h"

#ifdef _WIN32
#include <Windows.h>
#endif

//#include"../Others/Windows.h"
//#include"../Graphics/Globals.h"

void Tsumego(Arbre&, Etat&);

class IA : public Arbre
{
public :
	//Infos methods
	void loadNumber(Arbre&);
	bool warning();
	//Tsumego methods 
	void Tsumego_naif(Arbre&, Etat&);
	void Tsumego_abr(Arbre&, Etat&);
};