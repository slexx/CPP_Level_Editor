#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <functional>
class MainMenu
{
public:
	MenuButton levelEditorButton;
	MenuButton gameButton;
	//init
	MenuWindow MainMenuWindow;

	MainMenu()
	{

		levelEditorButton.text.setString("Level Editor");
		levelEditorButton.rect.setSize(sf::Vector2f(levelEditorButton.text.getGlobalBounds().width + 6, levelEditorButton.text.getGlobalBounds().height + 6));

		levelEditorButton.rect.setPosition(sf::Vector2f(MainMenuWindow.windowWidth - (levelEditorButton.rect.getSize().x / 2) , MainMenuWindow.windowWidth - 20));
		levelEditorButton.text.setPosition(levelEditorButton.rect.getPosition().x + (levelEditorButton.rect.getSize().x / 400000), levelEditorButton.rect.getPosition().y);

		gameButton.text.setString("Game");
		gameButton.rect.setSize(sf::Vector2f(gameButton.text.getGlobalBounds().width + 6, gameButton.text.getGlobalBounds().height + 6));

		gameButton.setPosition(sf::Vector2f(MainMenuWindow.windowWidth - (levelEditorButton.rect.getSize().x / 2), MainMenuWindow.windowWidth + 20));
		gameButton.text.setPosition(gameButton.rect.getPosition().x + (gameButton.rect.getSize().x / 400000), gameButton.rect.getPosition().y);
	}


	bool Start();
	int Update();
};

class EditorLevelSelect
{

};

class GameLevelSelect
{

};

class MenuButton : public sf::Drawable, public sf::Transformable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(rect, states);
		target.draw(text, states);
	}
public:
	int textSize = 30;
	float rectOutline = 1;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
	sf::FloatRect rBounds;
	MenuButton()
	{
		font.loadFromFile("OpenSans-Regular.ttf");
		text.setFont(font);
		text.setCharacterSize(textSize);
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

class MenuWindow
{
public:
	//setup window size
	const int windowWidth = 1025;
	const int windowHeight = 650;

	//mouse position 
	sf::Vector2f worldPos;
	sf::RenderWindow window;
	//MenuWindow() {}


};



