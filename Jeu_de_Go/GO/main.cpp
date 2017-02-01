#include <iostream>
#include <vector>
#include "Etat.h"
#include "Goban.h"
using namespace std;

bool EstVoisine(const Etat& maPiece, const Etat& autrePiece){
  size_t m_x, m_y, o_x, o_y;
  m_x = maPiece.getX();
  m_y = maPiece.getY();
  o_x = autrePiece.getX();
  o_y = autrePiece.getY();
  if ( o_x == (m_x-1) || o_x == (m_x+1) || o_x == m_x){
    if (o_y == (m_y-1) || o_y == (m_y+1) || o_y == m_y){
      if (o_x!=m_x || o_y!=m_y){
        return true;
      }
    }
  }
return false;
}
int main(){

  //DECLARATIONS
  Goban goban;
  vector<vector<Etat> > GroupesNoirs (0);//BLACK GROUPS
  vector<vector<Etat> > GroupesBlanches (0);//WHITE GROUPS

  //INITIALIZATION OF GOBAN (GROUPE GRAPHISME)
  cout<<goban;
  goban[0].setVal(NOIR);
  goban[10].setVal(NOIR);
  goban[20].setVal(NOIR);
  goban[30].setVal(NOIR);
  goban.coord(1,4).setVal(BLANC);
  goban.coord(0,4).setVal(BLANC);

  //DEFINE GROUPS IN THE CURRENT GOBAN
  vector<Etat> tmpGroupe (0);
  size_t k=0;//groups counter
  size_t j=0;//stones counter
  bool findGroup=false;//exit the loop if group found

  for (size_t i=0; i < (TGOBAN * TGOBAN); i++){
    findGroup=false;
      if (goban[i].getVal()!=VIDE && goban[i].getVal()!=KO){
        if (goban[i].getVal()==NOIR){
          if (GroupesNoirs.size()==0){//if there's no black groups
              cout<<"le premier "<<goban[i]<<endl;
              tmpGroupe.push_back(goban[i]);
              GroupesNoirs.push_back(tmpGroupe);
              tmpGroupe.resize(0);
          }
          else{//if there's black groups search a neighboor-group
            while (k<GroupesNoirs.size() && !findGroup) {
              while (j<GroupesNoirs[k].size() && !EstVoisine(goban[i],GroupesNoirs[k][j])){
                j++;
              }
              if (j<GroupesNoirs[k].size()){//insert stone in group
                GroupesNoirs[k].push_back(goban[i]);
                findGroup=true;
              }
              j=0;
              k++;
            }
            k=0;
            if (!findGroup){//create new black group
              tmpGroupe.push_back(goban[i]);
              GroupesNoirs.push_back(tmpGroupe);
              tmpGroupe.resize(0);
            }
          }
        }
        else{
          //LA MEME CHOSE QUE LES LIGNES 41-64
          size_t k=0;//groups counter
          size_t j=0;//stones counter
          bool findGroup=false;
          if (goban[i].getVal()==BLANC){
            if (GroupesBlanches.size()==0){//if there's no black groups
                tmpGroupe.push_back(goban[i]);
                GroupesBlanches.push_back(tmpGroupe);
                tmpGroupe.resize(0);
            }
            else{//if there's black groups search a neighboor-group
              while (k<GroupesBlanches.size() && !findGroup) {
                while (j<GroupesBlanches[k].size() && !EstVoisine(goban[i],GroupesBlanches[k][j])){
                  j++;
                }
                if (j<GroupesBlanches[k].size()){//insert stone in group k
                  GroupesBlanches[k].push_back(goban[i]);
                  findGroup=true;
                }
                j=0;
                k++;
              }
              k=0;
              if (!findGroup){//create new black group
                tmpGroupe.push_back(goban[i]);
                GroupesBlanches.push_back(tmpGroupe);
                tmpGroupe.resize(0);
              }
            }
          }
        }
      }
    }


afficheGroupes(GroupesNoirs);
afficheGroupes(GroupesBlanches);

return 0;
}
