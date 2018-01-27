#include "main.h"

sf::Vector2i map[150][150];
sf::Vector2i loadCounter = sf::Vector2i(0, 0);
sf::Texture tileTexture;
sf::Sprite tiles;

class Player
{
public:
	sf::RectangleShape rect;
	float bottom, left, right, top;

	Player(sf::Vector2f position, sf::Vector2f size, sf::Color color)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(color);
	}

	void Update()
	{
		bottom = rect.getPosition().y + rect.getSize().y;
		left = rect.getPosition().x;
		right = rect.getPosition().x + rect.getSize().x;
		top = rect.getPosition().y;
	}

	bool Collision(Player p)
	{
		if (right < p.left || left > p.right || top > p.bottom || bottom < p.top)
		{
			return false;
		}
		return true;
	}
};

int main() {

	sf::Event event;
	sf::ContextSettings settings;

	std::ifstream openfile("./src/map/map1.txt");

	if (openfile.is_open())
	{
		std::string tileLocation;
		openfile >> tileLocation;
		tileTexture.loadFromFile(tileLocation);
		tiles.setTexture(tileTexture);
		while (!openfile.eof())
		{
			std::string str;
			openfile >> str;
			char x = str[0], y = str[2];
			if (!isdigit(x) || !isdigit(y))
			{
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(-1, -1);
			}
			else
			{
				map[loadCounter.x][loadCounter.y] = sf::Vector2i(x - '0', y - '0');
			}
			if (openfile.peek() == '\n')
			{
				loadCounter.x = 0;
				loadCounter.y++;
			}
			else
			{
				loadCounter.x++;
			}
		}
	}


	//24 tiles height, 32 width
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Ricochet", sf::Style::Titlebar | sf::Style::Close);

	window.setFramerateLimit(60);

	Player p1(Player(sf::Vector2f(10, 10), sf::Vector2f(20, 20), sf::Color::Red)), p2(Player(sf::Vector2f(100, 100), sf::Vector2f(20, 20), sf::Color::Blue));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}

		}

		window.clear();

		for (int i = 0; i < loadCounter.x; i++)
		{
			for (int j = 0; j < loadCounter.y; j++)
			{
				if (map[i][j].x != -1 && map[i][j].y != -1)
				{
					tiles.setPosition(i * 32, j * 32);
					tiles.setTextureRect(sf::IntRect(map[i][j].x * 32, map[i][j].y * 32, 32, 32));
					window.draw(tiles);
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			p1.rect.move(1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			p1.rect.move(-1, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			p1.rect.move(0, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			p1.rect.move(0, 1);
		}

		p1.Update();
		p2.Update();

		if (p1.Collision(p2))
		{
			std::cout << "Collision" << std::endl;
		}

		window.draw(p1.rect);
		window.draw(p2.rect);
		window.display();

	}

	///End of execution
}