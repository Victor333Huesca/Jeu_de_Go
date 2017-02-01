#ifndef Goban_H
#define Goban_H
#include <iostream>
#include <vector>
#include "Etat.h"
using namespace std;

//Goban's size
const size_t TGOBAN=10;

class Goban{
private:
  Etat* array;

public:
  //CONSTRUCTORS
  Goban();//default constructor

  //METHODES
  Etat& coord(const int,const int);//access to element of array with (x,y)

  //overloadings methodes
  Etat& operator[](const size_t) const;
};

//overloadings functions
ostream& operator<<(ostream&, const Goban&);

void afficheGroupes(vector<vector<Etat> >);
#endif
