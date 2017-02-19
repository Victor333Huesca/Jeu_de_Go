#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}

int Parser::goIntoSgf(const std::string & src_name, const std::string& out_name) const
{
	char ch;
	size_t x, y;
	char state;								 // B: black, W: white, _: null
	char goban[NB_SQUARES_X][NB_SQUARES_Y];

	// Initialize the goban
	for (int i = 0; i < NB_SQUARES_X; i++)
	{
		for (int j = 0; j < NB_SQUARES_Y; j++)
		{
			goban[i][j] = '_';
		}
	}

	// Start reading the .sgf file
	std::ifstream src_file(src_name);
	if (!src_file.fail())
	{
		// While the file isn't ended
		while (src_file.get(ch) && ch != EOF)
		{
			// Look for the ; instuction
			if (ch == ';')
			{
				// Read the instuction
				src_file.get(ch);
				state = ch;

				// Ignore the [ then read the abscissa
				src_file.get(ch);
				src_file.get(ch);
				x = (size_t)ch;

				// Read the ordinate
				src_file.get(ch);
				y = (size_t)ch;

				// Transform coordinates from letters a-s to 0-18
				x = x - 97;
				y = y - 97;

				// Set up the value
				goban[x][y] = state;
			}
		}
	}
	else
	{
		std::cerr << "Impossible d'ouvrir le fichier .sgf !" << std::endl;
		return 1;
	}
	src_file.close();

	// Start writing the .go file
	std::ofstream out_file(out_name);
	if (!out_file.fail())
	{
		for (int i = 0; i < NB_SQUARES_X; i++)
		{
			for (int j = 0; j < NB_SQUARES_Y; j++)
			{
				out_file << goban[i][j];
			}
			out_file << "\n";
		}
	}
	else
	{
		std::cerr << "Impossible d'écrire le fichier .go !" << std::endl;
		return 1;
	}
	out_file.close();

	return 0;
}