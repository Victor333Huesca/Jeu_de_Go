#include <iostream>
#include <vector>
#include "Etat.h"
#include "Goban.h"

using namespace std;

//CONSTRUCTORS

Goban::Goban(){
  array= new Etat[TGOBAN*TGOBAN];
  size_t i=0;
  for (size_t y=0;y<TGOBAN; y++){
    for (size_t x=0;x<TGOBAN; x++){
      array[i].setX(x);
      array[i].setY(y);
      array[i].setVal(VIDE);
      i++;
    }
  }
}

//overloadings methodes

Etat& Goban::operator[](const size_t i)const{
  return array[i];
}

//METHODES

Etat& Goban::coord(const int X,const int Y){//access to element of array with (x,y)
  size_t i=TGOBAN*Y+X;
  return array[i];
}

//overloadings functions
ostream& operator<<(ostream& os, const Goban& goban){
  size_t i=0;
  for (size_t y=0;y<TGOBAN; y++){
    for (size_t x=0;x<TGOBAN; x++){
      os<<goban[i].getVal()<<" ";
      i++;
    }
    os<<endl;
  }
  return os;
}

//print all the groupe of single color stone
void afficheGroupes(vector<vector<Etat> > groupe){
  for(size_t i=0 ; i<groupe.size() ; i++){
    cout<<"le groupe "<<i+1<<" {";
    for(size_t j=0; j<groupe[i].size() ; j++){
    cout<<groupe[i][j];
    }
    cout<<"}"<<endl;
  }
}
