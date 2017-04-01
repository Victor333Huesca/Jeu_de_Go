#include "Choice.h"
#include <iostream>

Choice::Choice(const char* name, sf::Vector2f pos, sf::Vector2f sc,const char* t,const char* ts) : //j'ai testé sans les const mais ce n'était pas ça
	selected(false)
{
	id = name;
	if (!sf.loadFromFile(ts))
		std::cout << "erreur lors de l'ouvertur du fichier" << std::endl;   //Je load le file pour le hoover
	if (!font.loadFromFile("./Ressources/Font/time.ttf"))
		std::cout << "erreur lors de l'ouvertur du fichier" << std::endl; // le petit font que j'ai mis en attribut de class
	if (!te.loadFromFile(t))
		std::cout << "erreur lors de l'ouvertur du fichier" << std::endl; //la texture pour le bouton !!
	//sprite.setTexture(te);
    // Set Common
    sprite.setPosition(pos);   //Bon là le bricolage de 2 sprites c'est osé mais fallait tenté ! et ca marche pas !
	sprite.setScale(sc);
	sprite2.setPosition(pos);
	sprite.setScale(sc);

	// Set the text
	text.setCharacterSize(45); //Macro ?
	text.setString(name);
	//text.setFont(font);
	text.setPosition(pos.x +100, pos.y -5); //Là c'est du bricolage de position mais je trouverai de quoi le mettre au milieu avec le getGlobalbound.
	text.setFillColor(sf::Color::Black); //J'ai pensé que c'était mieux en noir, surtout qu'en blanc par défaut quand les texture fuité ....
}

Choice::Choice(const char * name, float posX, float posY, sf::Vector2f sc,const char* t,const char* ts) :
	Choice(name, sf::Vector2f(posX, posY), sc, t, ts)
{

}

Choice::~Choice()
{
}

void Choice::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//sprite.setTexture(te);
	sf::Sprite spr;   //Je pense qu'il y a une fuite mémoire pour la texture et le font .. 
	sf::Sprite sprs;  //Stade ultime du bricolage dégueulasse mais bon faut bien faire des tests (ps : ca ne fonctionne pas car 
	spr = sprite;    //l'attribut selected ne passe pas a true) en fait je ne sais pas pourquoi même un attribut booléen ne se modifie pas
	sprs = sprite2;
	spr.setTexture(te);
	sprs.setTexture(sf);
	if (!selected)
	{
		target.draw(spr, states);
	}
	else
	{
		target.draw(sprs, states);  //<- quand ce bricolage n'a pas fonctionné je me suis dit : là on y est 
	}
	sf::Text txt;

	txt = text;
	txt.setFont(font);
	//text.setFont(font);  //Je suis sur qu'on se rendre que c'est un truc tout bête. 
	
	//target.draw(spr, states);   
	target.draw(txt, states); //Ou alors résoudre un prix du millénaire !
}

sf::Vector2f Choice::getSize() const
{
    return sf::Vector2f(sprite.getTextureRect().width, sprite.getTextureRect().height);
}

void Choice::move(const sf::Vector2f & offset)
{
	sprite.move(offset);
}

bool Choice::Click(int x, int y)  //normalement je fais ca avec getGlobalBound mais il n'arrive pas à récupérer toute les données ...
{
	/*sf::Vector2f point(x, y);
	sf::FloatRect box = sprite.getGlobalBounds();

	return box.contains(point);*/   //Voilou du coup petit bricolage à la main avec les chiffres et tout en attendant de trouver la source du pb.
	return (x < sprite.getPosition().x + 374) && (y < sprite.getPosition().y + 54) && (x > sprite.getPosition().x) && (y > sprite.getPosition().y);
}

void Choice::setSelected(bool b)
{
	selected = b;
}

bool Choice::getSelected()
{
	return selected;    
}

void Choice::loadTextures(const sf::Texture & blank, const sf::Texture & selected)
{
	t_blank = &blank;
	t_selected = &selected;
/*
	sprite.setTexture(*t_blank, true);   //je ne sais plus pourquoi j'ai commenté ça

	std::cout << text.getString().toAnsiString() << " : (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")   -->   ";
	std::cout << "Texture's size : (" << t_blank->getSize().x << ", " << t_blank->getSize().y << ")" << std::endl;*/
}
