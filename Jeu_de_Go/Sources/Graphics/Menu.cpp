#include "Menu.h"


Menu::Menu(const sf::Vector2f & position, const char* texture, const char* font, sf::Vector2f & scale) :
	cur_choice(nullptr)
{
	t_background.loadFromFile(texture);
	s_background.setTexture(t_background);
	s_background.setPosition(position);
	s_background.setScale(scale);

	text_font.loadFromFile(font);
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(s_background, states);
    for (const Choice& choice : choices)
        target.draw(choice, states);
}

int Menu::Run(sf::RenderWindow &window)
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
			{
				int res = click(event.mouseButton.button, window);
				if (res != NO_CHANGE)
					return res;
				break;
			}
			case sf::Event::MouseMoved:
				mouseMoved(window, sf::Mouse::getPosition(window));
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

sf::Vector2f Menu::getSize() const
{
    return sf::Vector2f(s_background.getTextureRect().width, s_background.getTextureRect().height);
}

sf::Vector2f Menu::getPosition() const
{
    return s_background.getPosition();
}


// Interactcions
int Menu::click(const sf::Mouse::Button& type, const sf::RenderWindow& window)
{
	if (cur_choice != nullptr)
		return cur_choice->Run(window);
	
	return NO_CHANGE;
	/*
	for (Choice& button : choices)   //j'ai travaillé ici car il faut renvoyé un int 
	{
		if (button.Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && (button.id == "Jouer"))
		{
			return 1;
		}
		if (button.Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && (button.id == "Quitter"))
		{
			return -1;
		}

	}


	// On récurpère la position de la souris
	sf::Vector2f position(sf::Mouse::getPosition(window));


	// Cherche le menu selectionné

	for (Choice& button : choices)
	{
	}
	*/
}

void Menu::mouseMoved(const sf::RenderWindow& window, sf::Vector2i pos)
{
	for (Choice& c : choices)
	{
		if (c.getGlobalBounds().contains(sf::Vector2f(pos)))
		{
			// c is hover
			if (cur_choice != &c)
			{
				// And it isn't the one selected
				c.setSelected(true);
				cur_choice = &c;
			}
		}
		else
		{
			// c isn't hover
			if (cur_choice != &c)
				// And it in not the one selected too
				c.setSelected(false);
		}
	}

	/*
	sf::Vector2f position(sf::Mouse::getPosition(window));
	for (Choice& button : choices)
	{
		if (button.Click(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			if (!button.getSelected())
			{
				button.setSelected(true);  //Voila ici ca ne fonctionne pas, alors ca affiche 1 tant qu'on est ici mais une fois sortie au revoir.
				
			}
				
			std::cout << button.getSelected() << std::endl;
		}
		else
		{
			std::cout << button.getSelected() << std::endl;
		}
		//button.setTexture("./Ressources/Img/button_blank.png");
	}
	*/
}

void Menu::keyPressed(const sf::Event::KeyEvent& key)
{

}

void Menu::addItem(Choice& item)
{
	item.setFont(text_font);
	choices.push_back(item);
}

void Menu::setItemsTextures(const char * blank, const char * selected)  // Quitte à avoir les boutons autant le déclarer direct au constructeur.
{
	// Load textures
	button_blank.loadFromFile(blank); 
	button_selected.loadFromFile(selected);
	
	// Apply to each choice
	for (Choice& c : choices)
		c.loadTextures(button_blank, button_selected);
}

