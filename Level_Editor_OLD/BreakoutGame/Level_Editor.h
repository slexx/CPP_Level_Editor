#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <list>
#include <functional>

class Actor : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
	}

public: 
	sf::Sprite sprite;

	enum Type
	{
		None,
		Player,
		Enemy,
		Coin,
		Spike,
		Exit
	};

	Type type = None;
	sf::Texture blankTexture;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture coinTexture;
	sf::Texture spikeTexture;
	sf::Texture doorTexture;
	Actor() {}

	void loadTextures() 
	{
		if (!blankTexture.loadFromFile("SpritesPlatformer/None.png"))
		{
			std::cout << "Failed to load None.png";
		}
		if (!playerTexture.loadFromFile("SpritesPlatformer/Player.png"))
		{
			std::cout << "Failed to load Player.png";
		}
		if (!enemyTexture.loadFromFile("SpritesPlatformer/EnemyAlive.png"))
		{
			std::cout << "Failed to load EnemyAlive.png";
		}
		if (!coinTexture.loadFromFile("SpritesPlatformer/Coin.png"))
		{
			std::cout << "Failed to load Coin.png";
		}
		if (!spikeTexture.loadFromFile("SpritesPlatformer/Spike.png"))
		{
			std::cout << "Failed to load Spike.png";
		}
		if (!doorTexture.loadFromFile("SpritesPlatformer/Door.png"))
		{
			std::cout << "Failed to load Door.png";
		}
	}

	void init(int x, int y)
	{
		loadTextures();
		sprite.setPosition(x, y);
		RefreshActor();
	}
	void ChangeActor(Type t) {
		type = t;
		RefreshActor();
	}

	void RefreshActor()
	{
		switch (type)
		{
		case None:
			sprite.setTexture(blankTexture);
			break;
		case Player:
			sprite.setTexture(playerTexture);
			break;
		case Enemy:
			sprite.setTexture(enemyTexture);
			break;
		case Coin:
			sprite.setTexture(coinTexture);
			break;
		case Spike:
			sprite.setTexture(spikeTexture);
			break;
		case Exit:
			sprite.setTexture(doorTexture);
			break;
		}
	}
};

class Tile : public sf::Drawable, public sf::Transformable {
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite, states);
		target.draw(actor, states);
	}
public:
	sf::Sprite sprite;
	Actor actor;
	enum Type
	{
		Sky,
		Platform,
		Lava
	};
	Type type = Sky;
	sf::Texture skyTexture;
	sf::Texture platformTexture;
	sf::Texture lavaTexture;
	sf::FloatRect rBounds;

	void loadTextures()
	{
		if (!skyTexture.loadFromFile("SpritesPlatformer/BlockSky.png"))
		{
			std::cout << "Failed to load BlockSky.png";
		}
		if (!platformTexture.loadFromFile("SpritesPlatformer/BlockPlatform.png"))
		{
			std::cout << "Failed to load BlockPlatformSky.png";
		}
		if (!lavaTexture.loadFromFile("SpritesPlatformer/BlockLava.png"))
		{
			std::cout << "Failed to load BlockLava.png";
		}
	}


	void init(int x, int y)
	{
		loadTextures();
		sprite.setPosition(x, y);
		actor.init(x, y);
		refreshTile();

	}

	void ChangeTile(Type t) {
		type = t;
		refreshTile();

	}
	//instead of using Tile.actor.changeactor

	void ChangeActor(Actor::Type a)
	{
		actor.ChangeActor(a);
	}

	bool mouseOver(sf::Vector2f windPos)
	{
		rBounds = sprite.getGlobalBounds();
		if (rBounds.contains(windPos.x, windPos.y))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void refreshTile()
	{
		switch (type)
		{
		case Sky:
			sprite.setTexture(skyTexture);
			break;
		case Platform:
			sprite.setTexture(platformTexture);
			break;
		case Lava:
			sprite.setTexture(lavaTexture);
			break;
		}
		actor.RefreshActor();
	}

};

class Button : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
public:
	int textSize = 16;
	float rectOutline = 1;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
	sf::FloatRect rBounds;
	Button()
	{
		font.loadFromFile("arial.ttf");
		text.setFont(font);
		text.setFillColor(sf::Color::Blue);
		text.setStyle(sf::Text::Regular);
		rect.setFillColor(sf::Color::White);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(rectOutline);
	}

	bool mouseOver(sf::Vector2f windPos)
	{
		rBounds = rect.getGlobalBounds();
		if (rBounds.contains(windPos.x, windPos.y))
		{
			rect.setOutlineThickness(rectOutline * 2);
			return true;
		}
		else
		{
			rect.setOutlineThickness(rectOutline);
			return false;
		}
	}

	// check for click, if so then pass
	void checkClick(std::function<void()> f, sf::Vector2f windPos)
	{
		if (mouseOver(windPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			f();
		}
	}


};

class ToolPanel : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		target.draw(loadButton);
		target.draw(saveButton);
	}
public:
	Button loadButton;
	Button saveButton;
	//init
	ToolPanel()
	{

		loadButton.text.setString("Load");
		loadButton.rect.setSize(sf::Vector2f(loadButton.text.getGlobalBounds().width + 6, loadButton.text.getGlobalBounds().height + 6));

		loadButton.rect.setPosition(sf::Vector2f(2, 20));
		loadButton.text.setPosition(loadButton.rect.getPosition().x + (loadButton.rect.getSize().x / 400000), loadButton.rect.getPosition().y);

		saveButton.text.setString("Save");
		saveButton.rect.setSize(sf::Vector2f(saveButton.text.getGlobalBounds().width + 6, saveButton.text.getGlobalBounds().height + 6));

		saveButton.setPosition(sf::Vector2f(2, 45));
		saveButton.text.setPosition(saveButton.rect.getPosition().x + (saveButton.rect.getSize().x / 400000), saveButton.rect.getPosition().y);
	}
};

class EditorClass
{
public:
	//grid amounts
	static const int x = 30;
	static const int y = 20;
	//track wether were painting with an acotr or a tile
	bool actorNotTile = false;
	//setup window size
	const int windowWidth = 1025;
	const int windowHeight = 650;

	//mouse position '
	sf::Vector2f worldPos;
	sf::View toolsView;
	sf::View levelEditView;
	sf::RenderWindow window;
	//setup variable to track selections
	Tile::Type curTileType;
	Actor::Type curActorType;
	//setup space for tool bar
	ToolPanel tools;

	//set up tils to select and paint with
	Tile tileButton[9];

	// setup tiules
	Tile tile[x][y];

	bool Start();
	int Update();

	//saving
	void save(Tile incTile[x][y])
	{
		//write text to a file
		std::ofstream myfile("save.sav");
		std::list<sf::Vector2i> coinPos;
		std::list<sf::Vector2i> enemyPos;
		std::list<sf::Vector2i> spikePos;
		sf::Vector2i playerPos;
		sf::Vector2i exitPos;

		if (myfile.is_open())
		{
			std::cout << "saving Tiles \n";
			for (int i = 0; i < x; i++)
			{
				for (int j = 0; j < y; j++)
				{
					switch (incTile[i][j].type)
					{
						//sky = 0, platfoprm = 1, lava = 2
					case Tile::Type::Sky:
						myfile << "0";
						break;
					case Tile::Type::Platform:
						myfile << "1";
						break;
					case Tile::Type::Lava:
						myfile << "2";
						break;

					}
					myfile << ",";
					switch (incTile[i][j].actor.type)
					{
					case Actor::Type::Coin:
						coinPos.push_back(sf::Vector2i(i, j));
						break;
					case Actor::Type::Enemy:
						enemyPos.push_back(sf::Vector2i(i, j));
						break;
					case Actor::Type::Spike:
						spikePos.push_back(sf::Vector2i(i, j));
						break;
					case Actor::Type::Player:
						playerPos = sf::Vector2i(i, j);
						break;
					case Actor::Type::Exit:
						exitPos = sf::Vector2i(i, j);
						break;
					}
				}
				myfile << "\n";


			}

			//loop through all of the lists, add them to the save file, then add the player and exit positions
			if (!coinPos.empty())
			{
				std::cout << "Saving Coins! \n";
				myfile << "Coin";
				std::list < sf::Vector2i >::iterator cIt;
				for (cIt = coinPos.begin(); cIt != coinPos.end(); cIt++)
				{
					sf::Vector2i curCoinPos = sf::Vector2i(cIt->x, cIt->y);
					std::cout << "Saving coin at: " << curCoinPos.x << "," << curCoinPos.y << "\n";
					myfile << '(' << curCoinPos.x << ',' << curCoinPos.y << ')';

				}
				myfile << "\n";
			}

			//enemy

			//spikes

			//player
			std::cout << "Saving player at: " << playerPos.x << ',' << playerPos.y << "\n";
			myfile << "Player" << '(' << playerPos.x << ',' << playerPos.y << ')' << "\n";

			//exit

			myfile.close();
			std::cout << "File saved! \n";
		}
		else
		{
			std::cout << "Cant open save file! \n";
		}

		//loading

		//printing out til;es

	}
	void load(Tile incTile[x][y])
	{
		std::string line;
		std::ifstream myfile("save.sav");
		if (myfile.is_open())
		{
			int a = 0;
			int b = 0;
			std::string saveHold;
			while (std::getline(myfile, line))
			{
				if (b == 0)
				{
					std::cout << "Loading Tiles \n";

				}
				if (b < x)
				{
					for (int i = 0; i < line.size(); i++)
					{


						switch (line[i])
						{
						case ',':
							a++;
							break;
						case '0':
							incTile[b][a].ChangeTile(incTile[a][b].Type::Sky);
							break;
						case '1':
							incTile[b][a].ChangeTile(incTile[a][b].Type::Platform);
							break;
						case '2':
							incTile[b][a].ChangeTile(incTile[a][b].Type::Lava);
							break;
						}

						incTile[b][a].refreshTile();
					}
				}
				else if (b >= x) // loading actors
				{
					//check the first two letters on lines after tiles are loaded ([Co]ins, [SP]ikes, [EN]emies etc
					std::string  lineHold = line;
					int curStart;
					int curEnd;
					std::string posString;
					if (line[0] == 'C' && line[1] == 'o') //[C][O]ins
					{
						std::cout << "Loading Coins! \n";
						while (curEnd < lineHold.length() && lineHold.find('(') != std::string::npos)
						{
							curStart = lineHold.find('(');
							curEnd = lineHold.find(')');
							posString = lineHold.substr(curStart + 1, curEnd - (curStart + 1));
							std::cout << "Loaded Coin at: " << posString << "\n";
							std::string xStr = posString.substr(0, posString.find(','));
							std::string yStr = posString.substr(posString.find(',') + 1, posString.length() - 1);
							incTile[std::stoi(xStr)][std::stoi(yStr)].actor.ChangeActor(Actor::Type::Coin);
							lineHold[curStart] = '<';
							lineHold[curEnd] = '>';
						}
					}
					else if (line[0] == 'E' && line[1] == 'n')
					{
						//enemy loading
					}
					else if (line[0] = 'S' && line[1] == 'p')
					{
						//spikes loading
					}
					else if (line[0] = 'P' && line[1] == 'l')
					{
						//player loading
						std::cout << "Loading Player! \n";
						// same as above	while(curEnd < lineHold.length() && lineHold.find('(') != std)
					}
					else if (line[0] = 'E' && line[1] == 'x')
					{
						// [E][x]it ;oading
					}
				}
				b += 1;
				a = 0;
			}
			myfile.close();
			std::cout << "File Loaded! \n";
		}
		else
		{
			std::cout << "Unable to open file \n";
		}
	}

};