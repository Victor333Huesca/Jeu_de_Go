#include "Game_window.h"

extern bool sound;

Game_window::Game_window() :
	board(sf::Vector2u(NB_SQUARES_X, NB_SQUARES_Y)),
	infos(),
	cur_player(Square::White)
{
	infos.setCurPlayer(Square::White);
}

Game_window::~Game_window()
{
}

void Game_window::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Save current view
	sf::View cur_view(target.getView());

	// Draw board
	target.setView(board.getView());
	target.draw(board, states);

	// Draw Infos Menu
	target.setView(infos.getView());
	target.draw(infos, states);

	// Set back previous view
	target.setView(cur_view);
}

Screens Game_window::Run(sf::RenderWindow &window, Go_Solver& solver)
{
	// To stay alive
	bool Running = true;
	Screens sc = NO_CHANGE;

	while (Running)
	{
		// Look each event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Differents event type
			switch (event.type)
			{
			case sf::Event::Closed:
				sc = EXIT;
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::MouseButtonReleased:
				sc = click(window, sf::Mouse::getPosition(window), event.mouseButton.button);
				break;
			case sf::Event::MouseWheelScrolled:
				zoom(event.mouseWheelScroll.delta, sf::Mouse::getPosition(window), window);
				break;
			case sf::Event::KeyPressed:
				sc = keyPressed(event.key);
				break;
			default:
				break;
			}

			if (sc != NO_CHANGE)
				return sc;
		}

		// Treate real-time actions

		// Linux version
#if !defined(_WIN32) && !MULTITHREAD
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw(*this);

		// End of current frame, display everything
		window.display();
#endif
	}


	// Not suppose to reach here but just in case
	return ERROR_SCREEN;
}

Screens Game_window::click(const sf::RenderWindow & window, sf::Vector2i pos, const sf::Mouse::Button & type)
{
	// Test if mouse was in the board or the info menu
	if (pos.x <= WINDOW_WIDTH)
	{
		// Get relative position inside the board's view
		pos = static_cast<sf::Vector2i>(window.mapPixelToCoords(pos, board.getView()));

		// Test if value has been changed
		if (board.click(pos, cur_player, type))
		{
			// Change next player info
			cur_player =
				cur_player == Square::Value::Black ?
				Square::Value::White :
				Square::Value::Black;
			infos.setCurPlayer(cur_player);
		}
		else // Value didn't changed
		{

		}
	}
	else // Not the board so infos's menu
	{

	}

	return NO_CHANGE;
}

void Game_window::zoom(const float delta, sf::Vector2i pos, sf::RenderWindow& window)
{
	// Get relative position inside the board's view
	pos = static_cast<sf::Vector2i>(window.mapPixelToCoords(pos, board.getView()));

	// Look if the mouse is on the board
	board.zoom(delta, pos);
}

Screens Game_window::keyPressed(const sf::Event::KeyEvent & key)
{
	if (key.control)
	{
		// Ctrl + ...

		if (key.code == sf::Keyboard::Z)
		{
			// Ctrl + Z
			board.cancel();
		}
		else if (key.code == sf::Keyboard::A)
		{
			territoire();
		}
		else if (key.code == sf::Keyboard::Y)
		{
			// Ctrl + Y
			// It will be more complecated than I expected.

			// Permet de lancezr le tsumego
			char c;
			std::cout << "Lancer le Tsumego Y/N ?  ";
			std::cin >> c;

			if (c == 'Y' || c == 'y')
			{
				std::cout << "lancement du tsumego :" << std::endl;
				Goban gob=board.getGoban();
				Arbre abr(gob, Etat::BLANC);
				//abr.Tsumego(board.getGoban().coord(1, 2));  //Erreur de free
				Tsumego(abr, board.getGoban().coord(0, 1));
			}
			else
			{
				std::cout << "Vous avez épargné votre pc !"<<std::endl;
			}
		}
	}
	else
	{
		if (key.code == sf::Keyboard::Escape)
		{
			// Escape
			return PAUSE;
		}
		// Not Ctrl
	}

	// Else
	return NO_CHANGE;
}

void Game_window::setGoban(const Goban & goban)
{
	board.load(goban);
}

void Game_window::setView(const sf::FloatRect& zone)
{
	board.setView(zone);
}

void Game_window::territoire()
{
	/*						A l'attention de Julien
		En faisant �a tu perds les avantages de l'encapsualtion, je m'explique :
			- Game_Window est la classe contenant une instance d'un jeu, c'est � dire
		l'�tat d'une partie de go mais aussi le menu contextuel trouvable sur le
		cot�. C'est cette classe qui g�re les entr�es / sorties et les transmet �
		qui de droit (ici c'est souvent au 'engine') qui lui traite cette information.
			- Board quand � elle est la classe qui g�re ce que repr�sente une partie de Go.
		C'est � dire toute les textures du plateau, la vu actuelle du (la partie
		zoom�e du plateau), et �videment la partie elle m�me (le fameau 'engine').
		Tout ces attributs DOIVENT �tre en PRIV� sous peine de donner un acc�s �
		des parties qui sont cruciales et doivent �tre contr�l�e. On ne veux pas en
		effet que n'importe qui tente de charger une texture comme �a lui plait sans
		passer la fonction qui permet elle de charger la texture de fa�on contr�l�e.
		De m�me pour modifier l'�tat du goban on passe par une m�thode et on ne touche
		jamais au grand jamais directement au goban lui-m�me.
			- Goban est la classequi g�re une partie de Go du point de vu des r�gles.
		En effet c'est elle qui valide ou non un coup, c'est elle qui permet de
		r�cup�rer des informations sp�cifique � une partie de Go qui, si les r�gle de
		ce jeu vennaient � varier- devrait �tre modifier sans que cela n'impacte le
		reste des classes Board et Game_window.
			- Il se trouve qu'ici Goban est aussi utilis�e pour jouer le tsumego, c'est un
		point de vu discutable car rajouter des fonctions telles que le tsumego
		directement � la classe l'allorudie et la rends bien moins modulaire.
		J'aurais plus la vision d'une classe specifique qui g�re ce genre de cas d'�tude.
		Apr�s c'est un ressenti et �tant donn� que ce projet n'est -� priori- qu'un
		"one shoot" et n'a donc pas pour but d'�tre repris, integrer directement des
		fonctinons en dur dans une classe est d�fendable. */

	// PS : Ne pas supprimer ce message, on doit pouvoir le r�utiliser pour le rapport.

	//L'id�e avait l'air sympathique � �xploiter.

	//Affiche le territoire de chaque joueur
	//Groupe groupsBlack, groupsWhite;
	//std::cout << board.engine.getGroupsBlack()[0]<< std::endl;
	/*for (size_t i = 0; i < 19; i++)
	{
		board.engine.coord(i, j).;
	}*/

	/*
	Pour chaque groupe renvoi le nombre d'oeil : 4 configuration
		-   (x-1, y) (x+1, y) (x, y-1) (x, y+1) (l'oeil classique)
		-   (x+1, y) (x, y+1) (l'oeil en coin)
		-   (x, y-1) (x+1, y) (x, y+1) (l'oeil de cot�
		-   (x-1, y) (x+2, y) (x, y-1) (x, y-1) (x, y+1) (x+1, y-1) (x+1, y+1) (grand oeil)

	ps : nous permettra de savoir si un groupe survivra sans arriv� � la fin d'une recherche (au moins deux yeux).

	Pour chaque groupe calcul la distance la plus courte avec les bords (haut, bas, droite, gauche)
		- Colore pour chaque groupe une t�che de la couleur du groupe de deux cases autour en direction du bords le plus proche.
		+ Colore l'int�rieur des yeux
		++ Si le groupe a moins de deux libert�s test� les deux coups pour pr�voir si il va mourir et le colorer de la couleur oppos�.


		*/
}

void Game_window::turnSoundsUp()
{
	board.turnSoundsUp();
}

void Game_window::turnSoundsDown()
{
	board.turnSoundsDown();
}
