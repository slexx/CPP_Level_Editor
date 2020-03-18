#include "Level_Editor.h"

int main()
{
	EditorClass myEditor;
	if (!myEditor.Start())
	{
		return EXIT_FAILURE;

	}
	return myEditor.Update();
	return 0;
}


bool EditorClass::Start()
{
	toolsView = sf::View(sf::FloatRect(0, 0, windowWidth * 0.045f, windowHeight));
	toolsView.setViewport(sf::FloatRect(0, 0, 0.045f, 1));
	levelEditView = sf::View(sf::FloatRect(0, 0, windowWidth, windowHeight));
	levelEditView.setViewport(sf::FloatRect(0.03f, 0, 1, 1));
	//setup the window
	window.create(sf::VideoMode(windowWidth, windowHeight), "Level Editor", sf::Style::Titlebar | sf::Style::Close);

	// setup variables to paint with
	curTileType = Tile::Type::Platform;
	curActorType = Actor::Type::Coin;

	for (int i = 0; i < 9; i++)
	{
		tileButton[i].init(10, (32 + 5) * i + 150);
	}

	tileButton[0].type = Tile::Type::Sky;
	tileButton[0].refreshTile();
	tileButton[1].type = Tile::Type::Platform;
	tileButton[1].refreshTile();
	tileButton[2].type = Tile::Type::Lava;
	tileButton[2].refreshTile();
	tileButton[3].actor.type = Actor::Type::None;
	tileButton[3].refreshTile();
	tileButton[4].actor.type = Actor::Type::Player;
	tileButton[4].refreshTile();
	tileButton[5].actor.type = Actor::Type::Enemy;
	tileButton[5].refreshTile();
	tileButton[6].actor.type = Actor::Type::Coin;
	tileButton[6].refreshTile();
	tileButton[7].actor.type = Actor::Type::Spike;
	tileButton[7].refreshTile();
	tileButton[8].actor.type = Actor::Type::Exit;
	tileButton[8].refreshTile();


	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++) {
			tile[i][j].init(i * 32 + ((windowWidth / 2) - ((32 * x) / 2)), j * 32);
		}
	}


	return true;

}

int EditorClass::Update()
{
	//game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		window.clear(sf::Color::White);
		window.setView(toolsView);

		worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		//loop through toolbar
		for (int i = 0; i < 9; i++)
		{
			if (tileButton[i].mouseOver(worldPos))
			{
				tileButton[i].sprite.setScale(sf::Vector2f(1.1f, 1.1f));
				tileButton[i].actor.sprite.setScale(sf::Vector2f(1.1f, 1.1f));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (i < 3)
					{
						actorNotTile = false;
						curTileType = tileButton[i].type;
					}
					else // 3 and above are actors
					{
						actorNotTile = true;
						curActorType = tileButton[i].actor.type;
					}
				}
			}
			else
			{
				tileButton[i].sprite.setScale(sf::Vector2f(1.0f, 1.0f));
				tileButton[i].actor.sprite.setScale(sf::Vector2f(1.0f, 1.0f));
			}
			window.draw(tileButton[i]);

		}



		window.draw(tools);
		window.setView(levelEditView);

		//draw our tiles
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				//check for click
				if (tile[i][j].mouseOver(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!actorNotTile)
					{
						tile[i][j].ChangeTile(curTileType);
					}
					else
					{
						tile[i][j].ChangeActor(curActorType);

					}
				}
				tile[i][j].refreshTile();
				window.draw(tile[i][j]);
			}
		}

		window.display();
	}
	//prep window for displaying stuff

	return 0;
}