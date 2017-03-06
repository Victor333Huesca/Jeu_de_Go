#include "Goban.h"
//PRIVATE METHODS
bool Goban::isMoveLegal(const int& x, const int& y) const
{
	return coord(x, y).isPlayable();
}

//CONSTRUCTORS
Goban::Goban() :
	array(nullptr),
	groups_white(0),
	groups_black(0),
	history()
{
  array= new Etat[TGOBAN*TGOBAN];
  size_t i=0;
  for (size_t y=0;y<TGOBAN; y++){
    for (size_t x=0;x<TGOBAN; x++){
      array[i].setX(x);
      array[i].setY(y);
      array[i].setVal(Etat::VIDE);
      i++;
    }
  }
}

//overloadings methodes

Etat& Goban::operator[](const size_t i)const{
  return array[i];
}

//METHODES

Etat& Goban::coord(const int& X,const int& Y){//access to element of array with (x,y)
  size_t i = TGOBAN * Y + X;
  return array[i];
}

const Etat& Goban::coord(const int& x, const int& y) const
{
	return array[TGOBAN * y + x];
}

size_t Goban::ctoi(const size_t X,const size_t Y)const{//convert coordonate of goban in index for the array
  return TGOBAN*Y+X;
}

std::ostream& Goban::afficheGroupes(std::ostream& stream, const Etat::VAL & val) const
{
	if (val == Etat::BLANC)
	{
		stream << "Groupes blancs : ";
		for (size_t i = 0; i < groups_white.size(); i++)
		{
			stream << groups_white[i] << "   ";
		}
	}
	else if (val == Etat::NOIR)
	{
		stream << "Groupes noirs : ";
		for (size_t i = 0; i < groups_black.size(); i++)
		{
			stream << groups_black[i] << "   ";
		}
	}
	else
	{
		stream << "Error : mauvais groupe demmand� !\n";
	}

	return stream;
}

std::ostream& Goban::afficheGroupes(std::ostream& stream) const
{
	// First White
	afficheGroupes(stream, Etat::BLANC);
	stream << std::endl;

	// Then Black
	afficheGroupes(stream, Etat::NOIR);
	stream << std::endl << std::endl;

	// And the history for pleasure
	stream << "Moves history : " << history << std::endl;

	return stream;
}

void Goban::rechercheGroupes(const Etat::VAL&  val, const bool& verbose)
{
	// Get the right group
	std::vector<Groupe>& groups = (val == Etat::BLANC ? groups_white : groups_black);

	// Reset groups to avoid fusion issue
	groups.clear();

	// Browse every goban's intersection
	for (size_t i = 0; i < (TGOBAN * TGOBAN); i++)
	{
		// If it's a stone of the color searched
		if (array[i].isAStone(val))
		{
			if (verbose)	std::cout << "Stone found.\n";

			// There is at least one group so start searching a neighboor-group
			size_t j = 0;
			while (j < groups.size())
			{
				if (verbose)	std::cout << "   Looking in the group " << j;
				// Look if the stone isn't already inside the group
				if (!groups[j].contain(array[i]))
				{
					if (verbose)	std::cout << "which not contain already that stone ";
					// So look if it should
					if (groups[j].shouldContain(array[i]))
					{
						if (verbose)	std::cout << "but which should, son include it.\n";
						groups[j].push_back(array[i]);
						j = groups.size() + 1;
					}
					else if (verbose)	std::cout << "because the stone is in an other group.\n";
				}
				else
				{
					j = groups.size() + 1;
					if (verbose)	std::cout << "which contain already the stone.\n";
				}
				j++;
			}
			// If no group has been found
			if (j == groups.size())
			{
				// Create a first group which contain only the current stone
				groups.push_back(Groupe(array[i]));
				if (verbose)	std::cout << "   No group found, a new group has been created.\n";
			}
		}
		if (verbose)	std::cout << "\n";
	}
}

void Goban::rechercheGroupes(const bool & verbose)
{
	rechercheGroupes(Etat::NOIR, verbose);
	rechercheGroupes(Etat::BLANC, verbose);
	fusionGroupes(groups_white);
	fusionGroupes(groups_black);
}

void Goban::fusionGroupes(std::vector<Groupe >& group){//fusion of eventual neighboor groupes
if (group.size()>0){
	for (size_t i=0; i< (group.size()-1);i++){//for each group
		for (size_t j=i+1; j< group.size();j++){
			if (group[i].voisin(group[j]) ){
				group[i].fusion(group[j]);
				group.erase(group.begin()+j);
			}
		}
	}
}
}

//LIBERTIES
void Goban::DefineStone(Etat& stone, size_t x, size_t y)const{//SAVE THE VALUE IN GOBAN(X,Y) IN STONE
  stone.setX(x);
  stone.setY(y);
  stone.setVal(array[ctoi(x,y)].getVal());
}
Groupe Goban::listOfLiberties(const Etat& stone){
  Etat tmpS;
  Groupe liberties;
  if (stone.getX()==TGOBAN-1 || stone.getY()==TGOBAN-1 || stone.getX()==0 || stone.getY()==0){//IF IN BORDURES
    if (stone.getX()==TGOBAN-1){
      if (stone.getY()==TGOBAN-1){
        this->DefineStone (tmpS, stone.getX()-1, stone.getY());
        liberties.push_back(tmpS);
        this->DefineStone (tmpS, stone.getX(),stone.getY()-1);
        liberties.push_back(tmpS);
      }
      else if (stone.getY()==0){
        this->DefineStone (tmpS, stone.getX()-1,stone.getY());
        liberties.push_back(tmpS);
        this->DefineStone (tmpS, stone.getX(),stone.getY()+1);
        liberties.push_back(tmpS);
      }
      else {
        this->DefineStone ( tmpS, stone.getX()-1,stone.getY());
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX(),stone.getY()-1);
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX(),stone.getY()+1);
        liberties.push_back(tmpS);
      }
    }


    if (stone.getY()==TGOBAN-1){
      if (stone.getX()==TGOBAN-1){
        this->DefineStone ( tmpS, stone.getX(),stone.getY()-1);
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX()-1,stone.getY());
        liberties.push_back(tmpS);
      }
      else if (stone.getX()==0){
        this->DefineStone ( tmpS, stone.getX(),stone.getY()-1);
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
        liberties.push_back(tmpS);
      }
      else {
        this->DefineStone ( tmpS, stone.getX(),stone.getY()-1);
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX()-1,stone.getY());
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
        liberties.push_back(tmpS);
      }
    }


    if (stone.getX()==0){
      if (stone.getY()==TGOBAN-1){
        this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX(),stone.getY()-1);
        liberties.push_back(tmpS);
      }
      else if (stone.getY()==0){
        this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX(),stone.getY()+1);
        liberties.push_back(tmpS);
      }
      else {
        this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX(),stone.getY()-1);
        liberties.push_back(tmpS);
        this->DefineStone ( tmpS, stone.getX(),stone.getY()+1);
        liberties.push_back(tmpS);
      }
		}

      if (stone.getY()==0){
        if (stone.getX()==TGOBAN-1){
          this->DefineStone ( tmpS, stone.getX(),stone.getY()+1);
          liberties.push_back(tmpS);
          this->DefineStone ( tmpS, stone.getX()-1,stone.getY());
          liberties.push_back(tmpS);
        }
        else if (stone.getX()==0){
          this->DefineStone ( tmpS, stone.getX(),stone.getY()+1);
          liberties.push_back(tmpS);
          this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
          liberties.push_back(tmpS);
        }
        else {
          this->DefineStone ( tmpS, stone.getX(),stone.getY()+1);
          liberties.push_back(tmpS);
          this->DefineStone ( tmpS, stone.getX()-1,stone.getY());
          liberties.push_back(tmpS);
          this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
          liberties.push_back(tmpS);
        }
      }
    }
  else {//IF STONE IS NOT IN THE BORDURE
      this->DefineStone ( tmpS, stone.getX()+1,stone.getY());
      liberties.push_back(tmpS);
      this->DefineStone ( tmpS, stone.getX()-1,stone.getY());
      liberties.push_back(tmpS);
      this->DefineStone ( tmpS, stone.getX(),stone.getY()+1);
      liberties.push_back(tmpS);
      this->DefineStone ( tmpS, stone.getX(),stone.getY()-1);
      liberties.push_back(tmpS);
  }
  return liberties;
}
void Goban::eliminateGroups(std::vector<Groupe >& GroupsColor){
  Groupe liberties;
  bool count =0;
  size_t j=0,//index of stones in a group
         k=0;//index of liberties
  for (size_t i=0; i< GroupsColor.size();i++){//for each group
    count =0;
    liberties.resize(0);
    j=0;
    while(!count && j< GroupsColor[i].size()){//for each stone of a group
      liberties=listOfLiberties(GroupsColor[i][j]);//define the list of liberties of the stone
      k=0;
			//std::cout<<"liberté: "<<liberties<<std::endl;;
      while (count==0 && k<liberties.size()){
        if (liberties[k].getVal()==Etat::VIDE || liberties[k].getVal()==Etat::KOWHITE || liberties[k].getVal()==Etat::KOBLACK){
          count++;
        }
        k++;
      }
      j++;
    }
    if (count==0){//group have to be eliminate from goban
      for (size_t z=0; z< GroupsColor[i].size();z++){
        this->coord(GroupsColor[i][z].getX(),GroupsColor[i][z].getY()).setVal(Etat::VIDE);
      }
      for (size_t h=i; h< GroupsColor.size()-1;h++){
        GroupsColor[h]=GroupsColor[h+1];//move groups backward
      }
      GroupsColor.erase(GroupsColor.begin()+GroupsColor.size()-1);//delete the last group after move groups back
    }
  }
}
void Goban::eliminateGroups(const Etat::VAL& value){
	if (value== Etat::BLANC)
		eliminateGroups(groups_black);
	else
		eliminateGroups(groups_white);
}

//other's methods
bool Goban::move(const Etat::VAL& value, const int& x, const int& y)
{
	if (isMoveLegal(x, y))
	{
		coord(x, y).setVal(value);
		history.add(Etat(x, y, value));

		return true;
	}

	return false;
}

bool Goban::cancel()
{
	// For the moment it only delete last stone placed but it should back to step n - 1.
	coord(history.current().getX(), history.current().getY()).setVal(Etat::VIDE);

	return history.cancel();
}

//overloadings functions
std::ostream& operator<<(std::ostream& os, const Goban& goban)
{
	size_t i=0;
	for (size_t y=0;y<TGOBAN; y++){
		for (size_t x=0;x<TGOBAN; x++){
			os << goban[i].getVal() << " ";
			i++;
		}
		os << std::endl;
	}

	return os;
}
