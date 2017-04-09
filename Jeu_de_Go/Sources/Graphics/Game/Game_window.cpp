#include "Game_window.h"



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

int Game_window::Run(sf::RenderWindow &window, Game_window&)
{
	// To stay alive
	bool Running = true;

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
				return EXIT;
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::MouseButtonReleased:
				click(window, sf::Mouse::getPosition(window), event.mouseButton.button);
				break;
			case sf::Event::MouseWheelScrolled:
				zoom(event.mouseWheelScroll.delta, sf::Mouse::getPosition(window), window);
				break;
			case sf::Event::KeyPressed:
				keyPressed(event.key);
				break;
			default:
				break;
			}
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
	return -1;
}

void Game_window::click(const sf::RenderWindow & window, sf::Vector2i pos, const sf::Mouse::Button & type)
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
}

void Game_window::zoom(const float delta, sf::Vector2i pos, sf::RenderWindow& window)
{
	// Get relative position inside the board's view
	pos = static_cast<sf::Vector2i>(window.mapPixelToCoords(pos, board.getView()));

	// Look if the mouse is on the board
	board.zoom(delta, pos);
}

void Game_window::keyPressed(const sf::Event::KeyEvent & key)
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
				Arbre abr(board.getGoban(), Etat::BLANC);
				abr.Tsumego(board.getGoban().coord(1, 2));  //Erreur de free
			}
			else
			{
				std::cout << "Vous avez épargné votre pc !"<<std::endl;
			}
		}
	}
	else
	{
		// Not Ctrl
	}
}

void Game_window::setGoban(const Goban goban)
{
	board.load(goban);
}

void Game_window::territoire()
{
	/*						A l'attention de Julien       
		En faisant ça tu perds les avantages de l'encapsualtion, je m'explique :
			- Game_Window est la classe contenant une instance d'un jeu, c'est à dire
		l'état d'une partie de go mais aussi le menu contextuel trouvable sur le 
		coté. C'est cette classe qui gère les entrées / sorties et les transmet à 
		qui de droit (ici c'est souvent au 'engine') qui lui traite cette information.
			- Board quand à elle est la classe qui gère ce que représente une partie de Go.
		C'est à dire toute les textures du plateau, la vu actuelle du (la partie 
		zoomée du plateau), et évidement la partie elle même (le fameau 'engine').
		Tout ces attributs DOIVENT être en PRIVÉ sous peine de donner un accès à
		des parties qui sont cruciales et doivent être contrôlée. On ne veux pas en 
		effet que n'importe qui tente de charger une texture comme ça lui plait sans 
		passer la fonction qui permet elle de charger la texture de façon contrôlée.
		De même pour modifier l'état du goban on passe par une méthode et on ne touche 
		jamais au grand jamais directement au goban lui-même.
			- Goban est la classequi gère une partie de Go du point de vu des règles.
		En effet c'est elle qui valide ou non un coup, c'est elle qui permet de 
		récupèrer des informations spécifique à une partie de Go qui, si les règle de 
		ce jeu vennaient à varier- devrait être modifier sans que cela n'impacte le 
		reste des classes Board et Game_window.
			- Il se trouve qu'ici Goban est aussi utilisée pour jouer le tsumego, c'est un
		point de vu discutable car rajouter des fonctions telles que le tsumego 
		directement à la classe l'allorudie et la rends bien moins modulaire.
		J'aurais plus la vision d'une classe specifique qui gère ce genre de cas d'étude.
		Après c'est un ressenti et étant donné que ce projet n'est -à priori- qu'un 
		"one shoot" et n'a donc pas pour but d'être repris, integrer directement des 
		fonctinons en dur dans une classe est défendable. */

	// PS : Ne pas supprimer ce message, on doit pouvoir le réutiliser pour le rapport.

	//L'idée avait l'air sympathique à éxploiter.

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
		-   (x, y-1) (x+1, y) (x, y+1) (l'oeil de coté
		-   (x-1, y) (x+2, y) (x, y-1) (x, y-1) (x, y+1) (x+1, y-1) (x+1, y+1) (grand oeil) 
	
	ps : nous permettra de savoir si un groupe survivra sans arrivé à la fin d'une recherche (au moins deux yeux).

	Pour chaque groupe calcul la distance la plus courte avec les bords (haut, bas, droite, gauche)
		- Colore pour chaque groupe une tâche de la couleur du groupe de deux cases autour en direction du bords le plus proche.
		+ Colore l'intérieur des yeux 
		++ Si le groupe a moins de deux libertés testé les deux coups pour prévoir si il va mourir et le colorer de la couleur opposé.


		*/
}
