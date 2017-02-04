#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include "Etat.h"
#include "Groupe.h"

//Goban's size
const size_t TGOBAN = 19;

class Goban{
private:
  Etat* array;
  std::vector<Groupe> groups_white;
  std::vector<Groupe> groups_black;

  // Privates methods
  Etat& coord(const int x, const int y);//access to element of array with (x,y)
  const Etat& coord(const int x, const int y) const;//access to element of array with (x,y)
  bool isMoveLegal(const int& x, const int& y) const;

public:
  //CONSTRUCTORS
  Goban();//default constructor

  //METHODES
  void afficheGroupes(const Etat::VAL& val) const;
  void afficheGroupes() const;
  void rechercheGroupes(const bool& verbose = false);
  
  // Return true if the move has been done, false otherwise.
  bool move(const Etat::VAL& value, const int& x, const int& y);

  //overloadings methodes
  Etat& operator[](const size_t) const;
};

//overloadings functions
std::ostream& operator<<(std::ostream&, const Goban&);
