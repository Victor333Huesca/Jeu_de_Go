#include "Menu.h"


Menu::Menu(const sf::Vector2f & position, const char* texture, const sf::Vector2f & scale) :
	choices(),
	cur_choice(nullptr)
{
	t_background.loadFromFile(texture);
	s_background.setTexture(t_background);
	s_background.setPosition(position);
	s_background.setScale(scale);

#if __ERROR_LEVEL__ > 0
	log_file << "Menu::Menu(), ";
#endif // __ERROR_LEVEL__ > 0
}

Menu::~Menu()
{
	for (Choice& c : choices)
	{
		Choice* cc = &c;
		delete cc;
	}

#if __ERROR_LEVEL__ > 0
	log_file << "Menu::~Menu()" << std::endl;
#endif // __ERROR_LEVEL__ > 0
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(s_background, states);

	for (const Choice& c : choices)
		target.draw(c, states);
}

int Menu::Run(sf::RenderWindow &window, Game_window& game)
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
				int res = click(event.mouseButton.button, window, game);
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
    return sf::Vector2f((float)s_background.getTextureRect().width, (float)s_background.getTextureRect().height);
}

sf::Vector2f Menu::getPosition() const
{
    return s_background.getPosition();
}


// Interactcions
int Menu::click(const sf::Mouse::Button& type, const sf::RenderWindow& window, Game_window& game)
{
	if (cur_choice != nullptr)
		return cur_choice->Run(window, game);
	
	return NO_CHANGE;
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
}

void Menu::keyPressed(const sf::Event::KeyEvent& key)
{

}

void Menu::addItem(Choice& item)
{
	Choice* _item = new Choice(item);
	choices.push_back(*_item);

#if __ERROR_LEVEL__ > 0
	log_file << "Menu::addItem(), ";
#endif // __ERROR_LEVEL__ > 0
}

void Menu::showAdresses() const
{
	std::cout << "\nTextures : " <<
		"\n  - Background : " << &t_background;

	for (Choice& c : choices)
		c.showAdressTextures();
}
