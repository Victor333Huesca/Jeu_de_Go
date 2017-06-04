#include "Parser.h"

// Passer le nom du fichier en param�tre ( a travers une future interface graphique?)
Goban parseur(std::string fichier)
{
	// On cr�e un goban vierge
	Goban goban;

	// on v�rifie que le fichier pass� en param�tre soit bien un .go
	if (std::regex_search(fichier, std::regex(".go")))
	{
		// C'est bien un .go --> On ouvre le fichier
		std::ifstream file(fichier);
		if (file)
		{
			// L'ouverture a r�ussie --> On lit le fichier
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
					std::cerr << "Caract�re lu inconnu � la position (" << x << ", " << y << ") !" << std::endl;
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
	// Je met ce retour uniquement pour que la fonction retourne bien ce qu'elle est suppo�e retourn�e.
	// En r�alit�e les 'else' pr�c�dents devraient lancer une exeption et ce cas ne sera jamais atteint,
	// c'est purement pour garder une coh�rence vis � vis tu type de retour.
	return Goban();
}
