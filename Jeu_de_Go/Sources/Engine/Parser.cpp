#include "Parser.h"
//using namespace std;

Goban parseur(std::string n_file)
{
	//std::string location = "./Ressource";
	std::ifstream file(n_file, std::ios::in);
	Goban goban;
	
	short int position = 0;
	char c;
	std::regex pattern{ ".go" };
	if (std::regex_search(n_file, pattern))
	{
		if (file)
		{

			do
			{
				position += 1;
				file.get(c);
				switch (c)
					{
					case 'B': 
						goban.coord(((position - 1) / TGOBAN), ((position - 1) % TGOBAN)).setVal(Etat::BLANC);
						break;		
					case '_': 
						goban.coord(((position - 1) / TGOBAN), ((position - 1) % TGOBAN)).setVal(Etat::VIDE);
						break;
					case 'N': 
						goban.coord(((position - 1) / TGOBAN), ((position - 1) % TGOBAN)).setVal(Etat::NOIR);
						break;
					}
				
			} while (c != EOF);
		}
	}
	return goban;
}
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