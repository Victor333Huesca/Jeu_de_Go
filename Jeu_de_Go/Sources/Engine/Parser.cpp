#include "Parser.h"

// Passer le nom du fichier en paramètre ( a travers une future interface graphique?)
Goban parseur(std::string fichier)
{
	// On crée un goban vierge
	Goban goban;

	// on vérifie que le fichier passé en paramètre soit bien un .go
	if (std::regex_search(fichier, std::regex(".go")))
	{
		// C'est bien un .go --> On ouvre le fichier
		std::ifstream file(fichier);
		if (file)
		{
			// L'ouverture a réussie --> On lit le fichier
			char piece;
			int x = 0, y = 0;

			while (file.get(piece))
			{
				switch (piece)
				{
				case 'B':
					goban.coord(x, y).setVal(Etat::BLANC);
					break;
				case '_':
					goban.coord(x, y).setVal(Etat::VIDE);
					break;
				case 'N':
					goban.coord(x, y).setVal(Etat::NOIR);
					break;
				case '-':
					goban.coord(x, y).setVal(Etat::NJ);
					break;
				case '\n':
					// Is okay on a juste lu un '\n'
					y++;
					break;
				default:
					std::cerr << "Caractère lu inconnu à la position (" << x << ", " << y << ") !" << std::endl;
					break;
				}

				// On avance les postions
				x < (int)TGOBAN ? x++ : x = 0;
			}
			return goban;
		}
		else
		{
			std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
		}
	}
	else
	{
		std::cerr << "Le fichier n'est pas un .go ! " << std::endl;
	}

	// Cet endroit est atteint en cas d'erreur (soit mauvaise extention, soit lecture imossible, etc...)
	// Je met ce retour uniquement pour que la fonction retourne bien ce qu'elle est suppoée retournée.
	// En réalitée les 'else' précédents devraient lancer une exeption et ce cas ne sera jamais atteint,
	// c'est purement pour garder une cohérence vis à vis tu type de retour.
	return Goban();
}
