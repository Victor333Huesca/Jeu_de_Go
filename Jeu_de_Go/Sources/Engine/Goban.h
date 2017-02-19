#pragma once
#include <iostream>
#include <vector>
#include "Etat.h"
#include "Groupe.h"
#include "History.h"

//Goban's size
const size_t TGOBAN = 19;

class Goban{
private:
  Etat* array;
  std::vector<Groupe> groups_white;
  std::vector<Groupe> groups_black;
  History history;

  // Privates methods
  Etat& coord(const int x, const int y);		// access to element of array with (x,y)
  const Etat& coord(const int x, const int y) const;		// access to element of array with (x,y)
  bool isMoveLegal(const int& x, const int& y) const;

public:
  //CONSTRUCTORS
  Goban();//default constructor

  //METHODES
  std::ostream& afficheGroupes(std::ostream& stream, const Etat::VAL& val) const;
  std::ostream& afficheGroupes(std::ostream& stream) const;
  void rechercheGroupes(const Etat::VAL&  val, const bool& verbose = false);
  void rechercheGroupes(const bool& verbose = false);

  // Return true if the move has been done, false otherwise.
  bool move(const Etat::VAL& value, const int& x, const int& y);

  //overloadings methodes
  Etat& operator[](const size_t) const;
};

//overloadings functions
std::ostream& operator<<(std::ostream&, const Goban&);
