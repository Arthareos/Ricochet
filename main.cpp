#include "main.h"

int main() {

	sf::Event event;
	sf::ContextSettings settings;

	sf::Vector2i map[150][150];
	sf::Vector2i loadCounter = sf::Vector2i(0, 0);
	sf::Texture tileTexture;
	sf::Sprite tiles;

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

		window.display();

	}

	///End of execution
}