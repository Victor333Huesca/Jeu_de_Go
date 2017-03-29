#include "Menu.h"


Menu::Menu(const sf::Vector2f & position, const char* texture, sf::Vector2f & sc)
{
	t_background.loadFromFile(texture);
	s_background.setTexture(t_background);
	s_background.setPosition(position);
	s_background.setScale(sc);
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(s_background, states);

    for (auto choice : choices)
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
				click(event.mouseButton.button, window);
				break;
			case sf::Event::MouseMoved:
				mouseMoved(window, sf::Mouse::getPosition(window));
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
void Menu::click(const sf::Mouse::Button& type, const sf::RenderWindow& window)
{
	// On récurpère la position de la souris
	sf::Vector2f position(sf::Mouse::getPosition(window));


	// Cherche le menu selectionné

	for (auto button : choices)
	{
	}
}

void Menu::mouseMoved(const sf::RenderWindow& window, sf::Vector2i pos)
{

}

void Menu::keyPressed(const sf::Event::KeyEvent& key)
{

}

void Menu::addItem(const Choice& item)
{
	choices.push_back(item);
}

void Menu::setItemsTextures(const char * blank, const char * selected)
{
	// Load textures
	button_blank.loadFromFile(blank);
	button_selected.loadFromFile(selected);

	// Apply to each choice
	/*for (auto c : choices)
	{
		c.loadTextures(button_blank, button_selected);
		std::cout << "Choix charge" << std::endl;
		//system("pause");
	}*/
}
