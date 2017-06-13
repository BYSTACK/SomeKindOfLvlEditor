#include "gameObject.h"



gameObject::gameObject()
{
	body.setSize(sf::Vector2f(30.f, 30.f));
	body.setPosition(0.f, 0.f);
	//body.setTexture(texture);
}

void gameObject::SetPos(int x, int y)
{
	this->x = x;
	this->y = y;

	body.setPosition((float)x, (float)y);
}
void gameObject::SetId(int id)
{
	this->textID = id;
}
void gameObject::SetDir(int dir)
{
	this->dir = dir;
}
void gameObject::SetShootDelay(int delay)
{
	this->shootDelay = delay;
}
void gameObject::SetShootOffset(int offset)
{
	this->shootOffset = offset;
}
void gameObject::SetType(std::string type)
{
	this->type = type;
	
}
void gameObject::SetLayer(int layer)
{
	this->layer = layer;
}
std::string& gameObject::GetType()
{
	return type;
}

int gameObject::GetX()
{
	return x;
}
int gameObject::GetY()
{
	return y;
}
int gameObject::GetSizeX()
{
	if (type == "Decoration")
	{
		return texture->getSize().x;
	}
	else
	{
		return 30;
	}
}
int gameObject::GetSizeY()
{
	if (type == "Decoration")
	{
		return texture->getSize().y;
	}
	else
	{
		return 30;
	}
}
std::string gameObject::Parse()
{
	std::string s;
	if (type == "Wall" || type == "Item" || type == "Spike")
	{
		s = type + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(textID);
	}
	else if (type == "Decoration")
	{
		s = type + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(textID) + " " + std::to_string(lightLevel) + " " + std::to_string(layer);
	}
	else if (type == "gravityChanger")
	{
		s = type + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(textID) + " " + std::to_string(textID);
	}
	else
	{
		s = type + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(dir) + " " + std::to_string(textID) + " " + std::to_string(shootDelay) + " " + std::to_string(shootOffset);
	}
	return s;
}

void gameObject::SetLightLevel(int lightLevel)
{
	this->lightLevel = lightLevel;
}

void gameObject::SetTexture(sf::Texture* texture)
{
	this->texture = texture;
	this->body.setTexture(this->texture);
	if (type == "Decoration")
	{
		body.setSize(sf::Vector2f(texture->getSize()));
	}
}
void gameObject::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

gameObject::~gameObject()
{
}
