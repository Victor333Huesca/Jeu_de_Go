#include<iostream>
#include"Arbre.h"

using namespace std;



int main(void)
{
	Goban G0;

	Arbre R(G0);
	Arbre A;
	A = R.InitArbre(G0, Etat::VAL::BLANC);

	cout << A << endl;



	return 0;
}