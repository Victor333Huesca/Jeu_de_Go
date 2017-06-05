#include "Goban.h"
//PRIVATE METHODS
bool Goban::isMoveLegal(const Etat::VAL& value, const int& x, const int& y) const
{
	bool eliminateKo = false, suicide;
	//Is it legal even if there's a KO
	if (value == Etat::BLANC){
		if (coord(x, y).getVal() == Etat::KOWHITE){
			eliminateKo= legalEvenKO(value,x,y);
		}
	}
	else {
		if (coord(x, y).getVal() == Etat::KOBLACK){
			eliminateKo= legalEvenKO(value,x,y);
		}
	}
	//IS IT AN EMPTY CASE
	if (coord(x, y).isPlayable(value,eliminateKo)){
		//IS IT A SUICIDE
		Etat stone (x, y, value);
		suicide=isSuicide(stone);
	}
	else return false;

	return !(suicide);
}

bool Goban::legalEvenKO(const Etat::VAL& value, const int& x, const int& y) const
{
	Goban GOB(*this);
	GOB.coord(x,y).setVal(value);
	GOB.rechercheGroupes();
	return GOB.eliminateOppGroups(value);
}

//CONSTRUCTORS
Goban::Goban() :
	array(nullptr),
	groups_white(0),
	groups_black(0),
	score_black(0),
	score_white(0),
	history()
{
	try
	{
		array = new Etat[TGOBAN*TGOBAN];
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
		exit(-1);
	}

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

Goban::Goban(const Goban& goban)
{
	if (&goban != this)
	{
		try
		{
			array = new Etat[TGOBAN * TGOBAN];
		}
		catch (const std::bad_alloc& e)
		{
			std::string msg = "Impossible d'allouer l'espace nécessaire à la création d'un Goban --> ";
			msg += e.what();
			log_file << msg;
			std::cerr << msg;

			throw e;
		}

		size_t i=0;
		for (size_t y=0;y<TGOBAN; y++)
		{
			for (size_t x=0;x<TGOBAN; x++)
			{
				array[i].setX(x);
				array[i].setY(y);
				array[i].setVal(goban.coord(x,y).getVal());
				i++;
			}
		}
	}
}
//DECONSTRUCTOR
Goban::~Goban(){
	delete[] array;
}
//overloadings methodes

Etat& Goban::operator[](const size_t i)const{
  return array[i];
}

//METHODES
Etat* Goban::getArray() {
	return array;
}

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

size_t* Goban::itoc(const size_t i) {//convert index in coordonates
	size_t y = i / TGOBAN;
	size_t x = i - y * TGOBAN;
	size_t* coor=new size_t(2);
	coor[0] = x;
	coor[1] = y;
	return coor;
}

//Accesseur
std::vector<Groupe> Goban::getGroupsWhite() const{
	return this->groups_white;
}
std::vector<Groupe> Goban::getGroupsBlack() const{
	return this->groups_black;
}

//ACCESSEURS AU SCORE
int Goban::getScoreBlack() const{
	return this->score_white;
}
int Goban::getScoreWhite() const{
	return this->score_white;
}

void Goban::setScoreBlack(int score){
	this->score_black += score;
}

void Goban::setScoreWhite(int score){
	this->score_white += score;
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
		stream << "Error : mauvais groupe demmandé !\n";
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
	size_t j=0;
	for (size_t i = 0; i < (TGOBAN * TGOBAN); i++)
	{
		// If it's a stone of the color searched
		if (array[i].isAStone(val))
		{
			if (verbose)	std::cout << "Stone found.\n";

			// There is at least one group so start searching a neighboor-group
			j = 0;
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
			if (group[i].voisin(group[j])){
				group[i].fusion(group[j]);
				group.erase(group.begin()+j);
				j--;
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
Groupe Goban::listOfLiberties(const Etat& stone) const{
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
bool Goban::eliminateGroups(std::vector<Groupe >& GroupsColor)
{
	int score=0;
	bool resultat=false;//FALSE if KO stay effective and TRUE if it's deleted
	Groupe liberties;
	bool estLibre = 0;
	size_t j=0,//index of stones in a group
		k=0;//index of liberties
	for (size_t i=0; i < GroupsColor.size();i++)
	{
		//for each group
		estLibre = 0;
		liberties.clear();
		j=0;
		while( !estLibre && j< GroupsColor[i].size())
		{
			//for each stone of a group
			liberties=listOfLiberties(GroupsColor[i][j]);//define the list of liberties of the stone
			k=0;
			//std::cout<<"liberté: "<<liberties<<std::endl;;
			while (!estLibre && k<liberties.size())
			{
				if (liberties[k].getVal()==Etat::VIDE || liberties[k].getVal()==Etat::KOWHITE || liberties[k].getVal()==Etat::KOBLACK || liberties[k].getVal()==Etat::NJ)
				{
					estLibre=1;
				}
				k++;
			}
			j++;
		}
		if (!estLibre)
		{
			//group have to be eliminate from goban
			if (GroupsColor[i].size() == 1){//1)control if KO have to been added.
				if (GroupsColor[i][0].getVal() == Etat::NOIR)
				{
					//IF KO BLACK
					this->coord(GroupsColor[i][0].getX(),GroupsColor[i][0].getY()).setVal(Etat::KOBLACK);
				}
				else
				{
					//IF KOWHITE
					this->coord(GroupsColor[i][0].getX(),GroupsColor[i][0].getY()).setVal(Etat::KOWHITE);
				}
			}
			else
			{
				//ELIMINATE GROUP
				resultat = true;
				for (size_t z=0; z< GroupsColor[i].size();z++)
				{
        			this->coord(GroupsColor[i][z].getX(),GroupsColor[i][z].getY()).setVal(Etat::VIDE);
					score++;
      			}
			}
			for (size_t h=i; h< GroupsColor.size()-1;h++)
			{
				GroupsColor[h]=GroupsColor[h+1];//move groups backward
			}
			GroupsColor.erase(GroupsColor.begin()+GroupsColor.size()-1);//delete the last group after move groups back
			i--; //test
		}
		/* --- Ceci est la cause du Bug sous Windows, étant donné que ce n'est pas essentiel ==> on supprime !
		if(score != 0)
		{
			if(GroupsColor[0][0].getVal() == Etat::NOIR)
			{
				this->setScoreWhite(score);
				score = 0;
			}
			else 
			{
				this->setScoreBlack(score);
				score = 0;
			}
  		}
		*/
	}
	return resultat;
}
bool Goban::eliminateOppGroups(const Etat::VAL& value){
	if (value== Etat::BLANC)
		return eliminateGroups(groups_black);
	else
		return eliminateGroups(groups_white);
}

bool Goban::isSuicide(const Etat& fStone) const{
	Groupe liberties;
	Etat::VAL actualColor;
	if(fStone.getVal() == Etat::BLANC){
		actualColor = Etat::BLANC;
	}
	else actualColor = Etat::NOIR;

  size_t i=0;//index of liberties
  liberties = listOfLiberties(fStone);
  while (i < liberties.size()){//if there's an empty liberty
    if (liberties[i].getVal()==Etat::VIDE || liberties[i].getVal()== Etat::KOWHITE || liberties[i].getVal()== Etat::KOBLACK || liberties[i].getVal()==Etat::NJ)
      return false;
    i++;
  }
  //an Hypotetic instance of the goban
  std::vector<Groupe> GroupsOpponentColor;
  Goban goban2(*this);
	if(actualColor == Etat::BLANC){
		GroupsOpponentColor = goban2.getGroupsBlack();
	}
	else{
		GroupsOpponentColor = goban2.getGroupsWhite();
	}

	//put the stone
	goban2.coord(fStone.getX(),fStone.getY()).setVal(fStone.getVal());
	//searching groups in goban2
	goban2.rechercheGroupes();
	//opponent group elimination after putting the fStone in goban2
	goban2.eliminateOppGroups(actualColor);
	std::vector<Groupe> GroupsOpponentColorAfter;
	std::vector<Groupe> GroupsToCheck;
	if(actualColor == Etat::BLANC){
		GroupsToCheck = goban2.getGroupsWhite();
		GroupsOpponentColorAfter = goban2.getGroupsBlack();
	}
	else{
		GroupsToCheck = goban2.getGroupsBlack();
		GroupsOpponentColorAfter = goban2.getGroupsWhite();
	}

//IF I KILL AN OPPONENT IT'S NOT SUICIDE, ELSE IF I KILL MY SELF IT'S SUICIDE
  if (GroupsOpponentColorAfter.size()<GroupsOpponentColor.size()) return false;//eliminate opponent's groups
  else {//if i kill myself it's suicide
			if (actualColor == Etat::BLANC){
				goban2.eliminateOppGroups(Etat::NOIR);
	    	if(GroupsToCheck.size()!=goban2.getGroupsWhite().size()) return true;
			}
			else{
				goban2.eliminateOppGroups(Etat::BLANC);
	    	if(GroupsToCheck.size()!=goban2.getGroupsBlack().size()) return true;
			}
	}
  return false;
}

//other's methods
bool Goban::move(const Etat::VAL& value, const int& x, const int& y)
{
	eliminateOppositeKO(value);
	if (isMoveLegal(value, x, y))
	{
		coord(x, y).setVal(value);
		history.add(Etat(x, y, value));

		return true;
	}

	return false;
}

void Goban::forceMove(const Etat::VAL& value, const int& x, const int& y)
{
	eliminateOppositeKO(value);
	
	coord(x, y).setVal(value);
	history.add(Etat(x, y, value));
}

bool Goban::cancel()
{
	// For the moment it only delete last stone placed but it should back to step n - 1.
	coord(history.current().getX(), history.current().getY()).setVal(Etat::VIDE);

	return history.cancel();
}

/* ---------- Compressions ----------- */

uint8_t * Goban::compress(int nb_revelent) const
{
	const Goban& goban = *this;

	const short unsigned used_bits = 2;	// Has to be a power of 2 lower than 8.

	// Firstly just count numher on revelent intersections if the user doesn't specify it
	if (!nb_revelent)
	{
		for (size_t i = 0; i < TGOBAN; i++)
		{
			for (size_t j = 0; j < TGOBAN; j++)
			{
				switch (goban.coord(i, j).getVal())
				{
				case Etat::VAL::BLANC:
				case Etat::VAL::NOIR:
				case Etat::VAL::VIDE:
				case Etat::VAL::KOBLACK:
				case Etat::VAL::KOWHITE:
					// The intersection has to be compressed in all these cases
					nb_revelent += used_bits;
					break;

				default:
					break;
				}
			}
		}
	}

	// So start compression now
	int nb_bytes = (int)ceil(nb_revelent / 8.f);			// 90.25 --> 91
	int nb_wasted_bits = 8 - nb_revelent % 8;		// 8 - 2  --> 6
	uint8_t* compressed = new uint8_t[nb_bytes];

	int current = 0;
	short int buff_used = 0;

	enum Codes : uint8_t { empty = 0, black = 1, white = 2, KO = 3 };

	for (size_t i = 0; i < TGOBAN; i++)
	{
		for (size_t j = 0; j < TGOBAN; j++)
		{
			switch (goban.coord(i, j).getVal())
			{
			case Etat::VAL::BLANC:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::white;
				buff_used += used_bits;
				break;

			case Etat::VAL::NOIR:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::black;
				buff_used += used_bits;
				break;

			case Etat::VAL::VIDE:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::empty;
				buff_used += used_bits;
				break;

			case Etat::VAL::KOBLACK:
			case Etat::VAL::KOWHITE:
				compressed[current] <<= used_bits;
				compressed[current] += Codes::KO;
				buff_used += used_bits;
				break;

			default:
				break;
			}

			if (buff_used == 8)
			{
				current++;
				buff_used = 0;
			}
		}
	}

	// Remplir le vide;
	compressed[nb_bytes - 1] <<= nb_wasted_bits;

	return compressed;
}

void Goban::uncompress(const uint8_t * compressed, const Etat::VAL KO_status, int nb_revelent)
{
	Goban& goban = *this;
	const short unsigned used_bits = 2;	// Has to be a power of 2 lower than 8.

										// Firstly just count numher on revelent intersections if the user doesn't specify it
	if (!nb_revelent)
	{
		for (size_t i = 0; i < TGOBAN; i++)
		{
			for (size_t j = 0; j < TGOBAN; j++)
			{
				switch (goban.coord(i, j).getVal())
				{
				case Etat::VAL::VIDE:
				case Etat::VAL::BLANC:
				case Etat::VAL::NOIR:
				case Etat::VAL::KOBLACK:
				case Etat::VAL::KOWHITE:
					// The intersection has to be compressed in all these cases
					nb_revelent += used_bits;
					break;

				default:
					break;
				}
			}
		}
	}

	int nb_bytes = (int)ceil(nb_revelent / 8.f);			// 90.25 --> 91
	int nb_wasted_bits = 8 - nb_revelent % 8;		// 8 - 2  --> 6

													// Start looking at the first place of the goban so -1 avoid skipping this first location.
	int current = -1;

	uint8_t masque = ~0;
	masque <<= (8 - used_bits);

	enum Codes : uint8_t { empty = 0, black = 1, white = 2, KO = 3 };

	// Read each byte untill last which contain waste
	for (int i = 0; i < nb_bytes - 1; i++)
	{
		// Read current
		int current_byte = compressed[i];

		for (int j = 0; j < 8; j += used_bits)
		{
			// Read bits
			int _tmp = (current_byte & masque) >> (8 - used_bits);
			current_byte <<= used_bits;
			assert(_tmp <= 3 && _tmp >= 0);				// Check that read value is correct
			Codes tmp = (Codes)_tmp;

			// Seach next available location in the goban
			do
			{
				current++;
			} while (goban[current].getVal() != Etat::VAL::VIDE &&
				goban[current].getVal() != Etat::VAL::BLANC &&
				goban[current].getVal() != Etat::VAL::NOIR &&
				goban[current].getVal() != Etat::VAL::KOBLACK &&
				goban[current].getVal() != Etat::VAL::KOWHITE);

			// Start interpreting
			switch (tmp)
			{
			case Codes::white:
				goban[current].setVal(Etat::VAL::BLANC);
				break;
			case Codes::black:
				goban[current].setVal(Etat::VAL::NOIR);
				break;
			case Codes::empty:
				goban[current].setVal(Etat::VAL::VIDE);
				break;
			case Codes::KO:
				goban[current].setVal(KO_status);
				break;
			default:
				std::cerr << "Error : Wrong Code readed \"" << tmp << "\" !" << std::endl;
				exit(-1);
				break;
			}
		}
	}

	// Read last byte
	int current_byte = compressed[nb_bytes - 1];
	for (int i = 0; i < 8 - nb_wasted_bits; i += used_bits)
	{
		// Read bits
		int _tmp = (current_byte & masque);
		current_byte <<= used_bits;
		assert(_tmp <= 3 && _tmp >= 0);				// Check that read value is correct
		Codes tmp = (Codes)_tmp;

		// Seach next available location in the goban
		do
		{
			current++;
		} while (goban[current].getVal() != Etat::VAL::VIDE &&
			goban[current].getVal() != Etat::VAL::BLANC &&
			goban[current].getVal() != Etat::VAL::NOIR &&
			goban[current].getVal() != Etat::VAL::KOBLACK &&
			goban[current].getVal() != Etat::VAL::KOWHITE);

		// Start interpreting
		switch (tmp)
		{
		case Codes::white:
			goban[current].setVal(Etat::VAL::BLANC);
			break;
		case Codes::black:
			goban[current].setVal(Etat::VAL::NOIR);
			break;
		case Codes::empty:
			goban[current].setVal(Etat::VAL::VIDE);
			break;
		case Codes::KO:
			goban[current].setVal(KO_status);
			break;
		default:
			std::cerr << "Error : Wrong Code readed \"" << tmp << "\" !" << std::endl;
			exit(-1);
			break;
		}
	}
}

/* ------- Fin de compression -------- */

  void Goban::eliminateOppositeKO(const Etat::VAL& value){
		if (value == Etat::BLANC){
			for (size_t i=0; i< TGOBAN*TGOBAN; i++){
				if (array[i].getVal()== Etat::KOBLACK)
					array[i].setVal(Etat::VIDE);
			}
		}
		else {
			for (size_t i=0; i< TGOBAN*TGOBAN; i++){
				if (array[i].getVal()== Etat::KOWHITE)
					array[i].setVal(Etat::VIDE);
			}
		}
	}

//overloadings functions
std::ostream& operator<<(std::ostream& os, const Goban& goban)
{
	size_t i=0;
	for (size_t y=0;y<4; y++){
		for (size_t x=0;x<5; x++){
			os << goban.coord(x,y).getVal() << " ";
			i++;
		}
		os << std::endl;
	}
	return os;
}


Goban Goban::operator= (const Goban& g)
{
	//std::cout << "Avant Goban::operator=" << std::endl;

	if (this != &g)
	{
		// Copy groupe 1
		groups_black.clear();
		groups_black.resize( g.groups_black.size());
		for (size_t i=0; i<g.groups_black.size();i++)
		{
			groups_black[i] = g.groups_black[i];
		}

		// Copy group 2
		groups_white.clear();
		groups_white.resize(g.groups_white.size());
		for (size_t i=0; i<g.groups_white.size();i++)
		{
			groups_white[i] = g.groups_white[i];
		}

		// copy history
		history = g.history;

		// Copy array
		try
		{
			delete[] array;
		}
		catch (const std::bad_alloc& e)
		{
			std::string msg = "Impossible de désaolouer un Etat[] pour la nouelle affectation d'un Goban --> ";
			msg += e.what();
			log_file << msg;
			std::cerr << msg;

			throw;
		}
		catch (const std::exception& e)
		{
			std::string msg = "Erreur inconnue --> ";
			msg += e.what();
			log_file << msg;
			std::cerr << msg;

			throw;
		}


		Etat* array2 = new Etat[TGOBAN * TGOBAN];
		for (size_t i = 0; i< TGOBAN * TGOBAN; i++)
		{
			array2[i] = g.array[i];
		}
		array=array2;
	}
	//std::cout << "Apres Goban::operator=" << std::endl;

	return *this;
}

//METHODES FOR THE TREE
std::vector<Goban> Goban::listFils(const Etat::VAL value) {
	//bool result = false;
	size_t x, y;
	std::vector<Goban> listGob(0);
	for (size_t i = 0; i < TGOBAN*TGOBAN; i++) {
		 x=itoc(i)[0];
		 y = itoc(i)[1];
		 //delete[] coordonates;
		 Goban g(*this);
		if (g.move(value, x , y))
		{
			// Move has been allowed
			//DEFINE GROUPS
			g.rechercheGroupes();

			//ELIMINATE GROUPS
			g.eliminateOppGroups(value);
			listGob.push_back(g);
		}
	}
	return listGob;
}
