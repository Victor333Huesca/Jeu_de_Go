#include "Globals.h"
#include "Main_window.h"
#include <thread>
#include <SFML/Network.hpp>
#include <ctime>

#define	MULTITHREAD false
#define PORT 53000

void renderingThread(Main_window* _window);
void connectToServer(sf::IpAddress server, unsigned short port);
void createServer(unsigned short port);


int main()
{
	// Globals
	bool online, host;

	// Try 1st
	char choice;
	do
	{
		std::cout << "A quel mode voulez-vous jouer, Local ou Online  ? ";
		std::cin >> choice;
	} while (choice != 'L' && choice != 'O');

	if (choice == 'O')
	{
		online = true;
		do
		{
			std::cout << "Souhaitez vous rejoindre un serveur existant ou en heberger un, Join ou Host ? ";
			std::cin >> choice;
		} while (choice != 'J' && choice != 'H');

		if (choice == 'H')
		{
			host = true;
			createServer(PORT);
		}
		else
		{
			host = false;
			sf::IpAddress adress;
			do
			{
				std::cout << "Quelle est l'adresse du serveur ? ";
				std::cin >> adress;
			} while (adress == sf::IpAddress::None);

			connectToServer(adress, PORT);
		}
	}
	else
	{
		online = false;
	}




	// Main's variables
	Main_window window(sf::VideoMode(WINDOW_WIDTH + INFOS_SIZE, WINDOW_WIDTH),	"Jeu de Go");

#if defined(_WIN32) || MULTITHREAD
	// disable window's context
	window.setActive(false);

	// Launch thread
	std::thread thread_rendering(renderingThread, &window);
#else
	window.setFramerateLimit(300);
#endif

	// Events loop
	while (window.isOpen())
	{
		// Look every event
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Differents event type
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::MouseButtonReleased:
				if (online)

				window.click(sf::Mouse::getPosition(window), event.mouseButton.button);
				break;
			case sf::Event::MouseWheelScrolled:
				window.zoom(event.mouseWheelScroll.delta, sf::Mouse::getPosition(window));
				break;
			case sf::Event::KeyPressed:
				window.keyPressed(event.key);
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
		window.draw();

		// End of current frame, display everything
		window.display();
#endif

	}

	// Wait for the rendering thread has finished its instructions before exit
#if defined(_WIN32) || MULTITHREAD
	thread_rendering.join();
#endif

	return 0;
}

void renderingThread(Main_window* _window)
{
	// Get the render window
	Main_window& window = *_window;
	window.setFramerateLimit(300);

	while (window.isOpen())
	{
		// Clear the window with a black screen
		window.clear(sf::Color::Black);

		// Draw everything here
		window.draw();

		// End of current frame, display everything
		window.display();
	}
}

void connectToServer(sf::IpAddress server, unsigned short port)
{
	// Create a socket for communicating with the server
	sf::TcpSocket socket;

	// Connect to the server
	if (socket.connect(server, port) != sf::Socket::Done)
		return;
	std::cout << "Connected to server " << server << std::endl;

	// Receive who start from server
	bool host_start;
	sf::Packet message;

	if (socket.receive(message) != sf::Socket::Done)
		return;
	message >> host_start;
	std::cout << std::boolalpha << "Server start the game : " << host_start << std::endl;
}

void createServer(unsigned short port)
{
	// Create a server socket to accept new connections
	sf::TcpListener listener;

	// Listen to the given port for incoming connections
	if (listener.listen(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

	// Wait for a connection
	sf::TcpSocket socket;
	if (listener.accept(socket) != sf::Socket::Done)
		return;
	std::cout << "Client connected: " << socket.getRemoteAddress() << std::endl;

	// Draw the player to play 1st
	srand(time(NULL));
	bool host_start = rand() % 2;

	sf::Packet message;
	message << host_start;
	
	// Send draw result
	if (socket.send(message) != sf::Socket::Done)
		return;
	std::cout << std::boolalpha << "Client has been informed that host start : " << host_start << std::endl;

}
