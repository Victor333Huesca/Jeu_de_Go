#include <SFML/Network.hpp>
#include <iostream>

int main()
{
	sf::TcpListener listener;
	unsigned short port = 53000;

	// lie l'écouteur à un port
	if (listener.listen(port) != sf::Socket::Done)
	{
		std::cerr << "Impossible d'ecouter sur le port " << port << "\n";
	}

	std::cout << "Server is listening to port " << port << ", waiting for connections... " << std::endl;

	// accepte le client 1
	sf::TcpSocket client1;
	if (listener.accept(client1) != sf::Socket::Done)
	{
		std::cerr << "Impossible d'accepter le client 1\n";
	}
	std::cout << "Client 1 connected : " << client1.getRemoteAddress() << std::endl;

	/*
	// accepte le client 2
	sf::TcpSocket client1;
	if (listener.accept(client1) != sf::Socket::Done)
	{
		std::cerr << "Impossible d'accepter le client 2\n";
	}
	std::cout << "Client 2 connected : " << client1.getRemoteAddress() << std::endl;
	*/


	// Tant que le client n'a pas demandé à se déconnecter
	bool exit = false;
	do
	{
		// Prépare le packet
		sf::Packet packet;
		packet << "Yolo";

		// Envoie le packet
		if (client1.send(packet) != sf::Socket::Done)
		{
			std::cerr << "Impossible d'envoyer le packet\n";
			exit = true;
		}
		std::cout << "Packet has been send\n";

		// Attend la réponse client
		if (client1.receive(packet) != sf::Socket::Done)
		{
			std::cerr << "Impossible de recevoir le packet client\n";
			exit = true;
		}
		std::cout << "Packet has been received\n";

	} while (!exit);

	return 0;
}