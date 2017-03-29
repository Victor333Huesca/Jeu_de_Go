#include <iostream>
#include <fstream>
#include "stdio.h"
#include "Goban.h"
#include <string>
#include <regex>
using namespace std;
/*
//VAL** parseur(string fichier){ //passer le nom du fichier en paramètre ( a travers une future interface graphique?)
ifstream file(fichier, ios::in);
extern int TGOBAN; // récupération de la taille du goban
VAL goban[TGOBAN][TGOBAN]; // création du tableau des états
int position=0;
std::regex pattern {".go"}; // on recherche les fichiers d'extensions .go

if (std::regex_search(fichier,pattern)) {
if(file) {
  do {
    position+=1;
    char piece;
    file.get(piece);
    switch(piece){

      case 'B': {
        goban[(( position - 1 ) / TGOBAN)][( (postion - 1) % TGOBAN )]=BLANC;
        break;
}
case '_': {
  goban[(( position - 1 ) / TGOBAN)][( (postion - 1) % TGOBAN )]=VIDE;
  break;
}
case 'N': {
  goban[(( position - 1 ) / TGOBAN)][( (postion - 1) % TGOBAN )]=NOIR;
  break;
}
    }
  } while(piece != EOF)

  return goban;


}
else { cout<<"Impossible d'ouvrir le fichier."<<endl;}

}

else { cout <<"Le fichier n'est pas un .go ! "<<endl;}


}
*/