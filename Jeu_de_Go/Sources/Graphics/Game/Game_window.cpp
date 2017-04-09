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
				return -1;
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
			size_t choix;
			std::cout << "\n_______________Parser v1.1 (console)________________ " << std::endl;
			std::cout << "Probl�me disponible (4) : " << std::endl;
			std::cout << "Veuillez choisir votre probl�me : ";
			std::cin >> choix;
			for (size_t x = 0; x < TGOBAN; x++)
			{
				for (size_t y = 0; y < TGOBAN; y++)
				{
					board.engine.coord(x, y).setVal(Etat::VIDE);
				}
			}
			board.load();
			for (size_t x = 9; x < TGOBAN; x++)
			{
				for (size_t y = 0; y < TGOBAN; y++)
				{
					board.engine.coord(x, y).setVal(Etat::NJ);
				}
			}
			for (size_t x = 0; x < TGOBAN; x++)
			{
				for (size_t y = 7; y < TGOBAN; y++)
				{
					board.engine.coord(x, y).setVal(Etat::NJ);
				}
			}
			switch (choix)
			{
			case 1:
				board.engine.coord(1, 3).setVal(Etat::NOIR);
				board.engine.coord(2, 3).setVal(Etat::NOIR);
				board.engine.coord(3, 3).setVal(Etat::NOIR);
				board.engine.coord(4, 3).setVal(Etat::NOIR);
				board.engine.coord(5, 3).setVal(Etat::NOIR);
				board.engine.coord(6, 3).setVal(Etat::NOIR);
				board.engine.coord(6, 2).setVal(Etat::NOIR);
				board.engine.coord(6, 1).setVal(Etat::NOIR);
				board.engine.coord(1, 5).setVal(Etat::NOIR);
				board.engine.coord(1, 2).setVal(Etat::BLANC);
				board.engine.coord(2, 2).setVal(Etat::BLANC);
				board.engine.coord(3, 2).setVal(Etat::BLANC);
				board.engine.coord(4, 2).setVal(Etat::BLANC);
				board.engine.coord(5, 2).setVal(Etat::BLANC);
				break;
			case 2: 
				board.engine.coord(3, 1).setVal(Etat::BLANC);
				board.engine.coord(4, 1).setVal(Etat::BLANC);
				board.engine.coord(6, 1).setVal(Etat::BLANC);
				board.engine.coord(7, 1).setVal(Etat::BLANC);
				board.engine.coord(4, 2).setVal(Etat::BLANC);
				board.engine.coord(6, 2).setVal(Etat::BLANC);
				board.engine.coord(5, 3).setVal(Etat::BLANC);
				board.engine.coord(6, 3).setVal(Etat::BLANC);
				
				board.engine.coord(3, 0).setVal(Etat::NOIR);

				board.engine.coord(2, 1).setVal(Etat::NOIR);
				board.engine.coord(8, 1).setVal(Etat::NOIR);

				board.engine.coord(3, 2).setVal(Etat::NOIR);
				board.engine.coord(7, 2).setVal(Etat::NOIR);
				board.engine.coord(9, 2).setVal(Etat::NOIR);

				board.engine.coord(3, 3).setVal(Etat::NOIR);
				board.engine.coord(4, 3).setVal(Etat::NOIR);
				board.engine.coord(7, 3).setVal(Etat::NOIR);

				board.engine.coord(5, 4).setVal(Etat::NOIR);
				board.engine.coord(6, 4).setVal(Etat::NOIR);
				board.engine.coord(7, 4).setVal(Etat::NOIR);
				break;
			case 3: 
				board.engine.coord(3, 0).setVal(Etat::BLANC);

				board.engine.coord(0, 1).setVal(Etat::BLANC);
				board.engine.coord(2, 1).setVal(Etat::BLANC);

				board.engine.coord(1, 2).setVal(Etat::BLANC);
				board.engine.coord(2, 2).setVal(Etat::BLANC);

				board.engine.coord(2, 3).setVal(Etat::BLANC);

				board.engine.coord(2, 4).setVal(Etat::BLANC);

				board.engine.coord(2, 5).setVal(Etat::BLANC);
				board.engine.coord(1, 5).setVal(Etat::BLANC);

				board.engine.coord(0, 6).setVal(Etat::BLANC);

				board.engine.coord(1, 0).setVal(Etat::NOIR);

				board.engine.coord(3, 1).setVal(Etat::NOIR);
				board.engine.coord(5, 1).setVal(Etat::NOIR);

				board.engine.coord(3, 2).setVal(Etat::NOIR);

				board.engine.coord(3, 3).setVal(Etat::NOIR);

				board.engine.coord(3, 4).setVal(Etat::NOIR);
				board.engine.coord(0, 4).setVal(Etat::NOIR);

				board.engine.coord(3, 5).setVal(Etat::NOIR);

				board.engine.coord(3, 6).setVal(Etat::NOIR);
				board.engine.coord(2, 6).setVal(Etat::NOIR);
				board.engine.coord(1, 6).setVal(Etat::NOIR);

				board.engine.coord(1, 8).setVal(Etat::NOIR);
				break;
			case 4:
				board.engine.coord(0, 3).setVal(Etat::BLANC);
				board.engine.coord(1, 3).setVal(Etat::BLANC);
				board.engine.coord(2, 3).setVal(Etat::BLANC);

				board.engine.coord(2, 2).setVal(Etat::BLANC);
				
				board.engine.coord(2, 1).setVal(Etat::BLANC);
				
				board.engine.coord(2, 0).setVal(Etat::BLANC);

				board.engine.coord(0, 4).setVal(Etat::NOIR);

				board.engine.coord(1, 4).setVal(Etat::NOIR);
				board.engine.coord(2, 4).setVal(Etat::NOIR);

				board.engine.coord(3, 4).setVal(Etat::NOIR);

				board.engine.coord(3, 3).setVal(Etat::NOIR);

				board.engine.coord(3, 2).setVal(Etat::NOIR);
				board.engine.coord(3, 1).setVal(Etat::NOIR);

				board.engine.coord(3, 0).setVal(Etat::NOIR);

				break;
			}
			
			char c;
			board.load();
			//std::cout << board.engine << std::endl;
			std::cout<<"Lancer le Tsumego Y/N ?  ";
			std::cin >> c;
			if (c == 'Y')
			{
				std::cout << "lancement du tsumego :" << std::endl;
				Arbre abr(board.engine, Etat::BLANC);
				abr.Tsumego(board.engine.coord(1, 2));  //Erreur de free
			}
			else
			{
				std::cout << "Vous avez �pargn� votre pc !"<<std::endl;
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
