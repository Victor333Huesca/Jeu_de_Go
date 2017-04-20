#pragma once
#include"Arbre.h"
//#include"../Graphics/Globals.h"

class IA : public Arbre
{
public :
	//Infos methods
	void loadNumber(Arbre&);
	bool warning();
	//Tsumego methods 
	void Tsumego_naif(Arbre&, Etat&);
	void Tsumego(Arbre&, Etat&);
};