#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;

typedef struct noeud {
  int info;
  struct noeud *sag;
  struct noeud *sad;} noeud;
typedef noeud *Abr;

Abr creerA(int p, Abr G, Abr D)
{
  Abr A = new noeud;
  A->info=p; A->sag=G; A->sad=D;
  return A;
}

void codageABdot(ofstream& fichier, Abr A){
  if (A != NULL){ 
    fichier << (long) A << " [label=\""  << A->info << "\" ] ;\n";
    if (A->sag != NULL) {
      fichier << (long)A << " -> " << (long)(A->sag) <<  " [color=\"red\",label=\"g\" ] ;\n";
      codageABdot(fichier,A->sag);} 
    if (A->sad != NULL) {
      fichier << (long)A << " -> " << (long)(A->sad) << " [color=\"blue\",label=\"d\" ] ;\n";
      codageABdot(fichier,A->sad);}
  }
  return;}
    

void dessinerAB(Abr A, const char * nomFic, string titre){
  ofstream f(nomFic);
  if (!f.is_open()){
   cout << "Impossible d'ouvrir le fichier en écriture !" << endl;
  }
  else {
    f<< "digraph G { label = \""<< titre << "\" \n";
    codageABdot(f,A);
    f << "\n }\n" ;
    f.close();}
  return;}

int main(void)
{
  int n;
  Abr A;
  ostringstream stre;
  string chaine;
  A=creerA(8,
		  creerA(2,
			 creerA(4,NULL,NULL),
				creerA(9,
					      NULL,
					      creerA(1,
							    NULL,
							    creerA(7,
									  creerA(11,NULL,NULL),
									  creerA(5, 
											NULL,
											NULL))))),
		  creerA(3,
				creerA(12,
					      creerA(6,NULL,NULL),
					      NULL),
				creerA(9,NULL,NULL)));
	  
  dessinerAB(A, "arbre.dot", "Arbre Bin");
  system("dotty arbre.dot");
  return 0;
}
