#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char** argv)
{
  ifstream PARAM_FILE(argv[1]); // .sgf
  ofstream OUT_FILE("data.go");
  char CHARACTERE;
  size_t X, Y; 
  char STATE; // B black W white _ null
  char GOBAN[19][19];  
  for(int i = 0; i < 19; i++)
    {
      for(int j = 0; j < 19; j++)
	{
	  GOBAN[i][j] ='_'; //INIT
	}
    }
 
  if(!PARAM_FILE.fail())
    {
      while(PARAM_FILE.get(CHARACTERE) && CHARACTERE != EOF)
	{
	  
	  if(CHARACTERE == ';')
	    {
	      PARAM_FILE.get(CHARACTERE);
	      STATE = CHARACTERE;
	      PARAM_FILE.get(CHARACTERE);
	      PARAM_FILE.get(CHARACTERE);
	      X = (size_t)CHARACTERE; //cat
	      PARAM_FILE.get(CHARACTERE);
	      Y = (size_t)CHARACTERE;
	      X = X - 97;  //ASCII 97 = a 
	      Y = Y - 97;
	      GOBAN[X][Y] = STATE;
	    }
	}
    }else
    {
      cerr << "impossible d'ouvrir le fichier !" << endl;
    }
  for(int i = 0; i < 19; i++)
    {
      for(int j = 0; j < 19; j++)
	{
	  OUT_FILE<<GOBAN[i][j];
        }
      OUT_FILE<<"\n";
    }
  OUT_FILE.close();
  PARAM_FILE.close();
  return 0;
}
