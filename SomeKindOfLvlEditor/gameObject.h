#pragma once
#include <string>
#include <SFML\Graphics.hpp>

class gameObject
{
private:
	int x, y,textID,dir,shootDelay,shootOffset,lightLevel, layer;
	std::string type;
	sf::Texture* texture;
	sf::RectangleShape body;
public:

	gameObject();
	void SetPos(int x, int y);
	void SetId(int id);
	void SetDir(int dir);
	void SetLightLevel(int lightLevel);
	void SetShootDelay(int delay);
	void SetShootOffset(int offset);
	void SetType(std::string type);
	void SetTexture(sf::Texture*);
	void SetLayer(int);
	
	std::string& GetType();
	int GetSizeX();
	int GetSizeY();
	int GetX();
	int GetY();

	void Draw(sf::RenderWindow& window);

	std::string Parse();
	~gameObject();
};

