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
  bool isMoveLegal(const int& x, const int& y) const;


public:
  //CONSTRUCTORS
  Goban();//default constructor

  // Access to a state
  Etat& coord(const int& x, const int& y);		// access to element of array with (x,y)
  const Etat& coord(const int& x, const int& y) const;		// access to element of array with (x,y)
  size_t ctoi(const size_t,const size_t)const;//convert coordonate of goban in index for the array

  //METHODES

  //GROUPS
  std::ostream& afficheGroupes(std::ostream& stream, const Etat::VAL& val) const;
  std::ostream& afficheGroupes(std::ostream& stream) const;
  void rechercheGroupes(const Etat::VAL&  val, const bool& verbose = false);
  void rechercheGroupes(const bool& verbose = false);
  void fusionGroupes(std::vector<Groupe >&);//fusion of eventual neighboor groupes

  //LIBERTIES AND ELIMINATION
  void DefineStone(Etat&, size_t, size_t) const;//define a stone with the value of the stone in the goban at (x,y)
  Groupe listOfLiberties(const Etat&);//define list of stones that are the liberties of stone passed in parametre
  void eliminateGroups(std::vector<Groupe >& GroupsColor);//eliminate from goban the groups tha don't have liberties
  void eliminateGroups(const Etat::VAL& value);//eliminate the opposite color's groups

  // Return true if the move has been done, false otherwise.
  bool move(const Etat::VAL& value, const int& x, const int& y);
  //return back to the state n-1 of the goban
  bool cancel();

  //overloadings methodes
  Etat& operator[](const size_t) const;
};

//overloadings functions
std::ostream& operator<<(std::ostream&, const Goban&);
