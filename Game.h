#pragma once
#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <random>
#include <functional>

#define NUM_GAMES 1

class button {
private:
	sf::Text title;
	sf::Color buttonColor;
	sf::RectangleShape buttonShape;
	bool clickFlagLeft;
	bool clickFlagRight;
	sf::Font buttonFont;
public:
	button(sf::Vector2f position, sf::Vector2f size, std::string title, sf::Font font);
	~button();
	bool isMouseOver(sf::RenderWindow* win);
	void clickHandle(sf::RenderWindow* win, const std::optional<sf::Event>& event);
	bool isClickedLeft();
	bool isClickedRight();
	void setColor(sf::Color color);
	void setPosition(sf::Vector2f newPos);
	void setSize(sf::Vector2f newSize);
	void draw(sf::RenderWindow* win);
	void dropClick();
	void setText(std::string text);
};

class imageButton{
private:
	sf::Sprite buttonSprite;
	bool clickFlagLeft;
	bool clickFlagRight;
public:
	imageButton(sf::Vector2f position, sf::Vector2f size, const sf::Texture& tex);
	~imageButton();
	bool isMouseOver(sf::RenderWindow* win);
	void clickHandle(sf::RenderWindow* win, const std::optional<sf::Event>& event);
	bool isClickedLeft();
	bool isClickedRight();
	void setTexture(const sf::Texture& newTex);
	void draw(sf::RenderWindow* win);
	void dropClick();
};

class Game;

class gameState {
private:
	sf::RenderWindow* win;
public:
	gameState() = default;
	virtual ~gameState();
	virtual void init(sf::RenderWindow* win);
	virtual void update(Game *game) = 0;
	virtual void handleInput(const std::optional<sf::Event>& event) = 0;
	virtual void render(sf::RenderWindow* win) = 0;
	virtual void clean();
};

class Game
{
private:
	std::stack<gameState*> states;
	sf::RenderWindow* win;
public:
	Game(sf::RenderWindow* win);
	~Game();
	void pushState(gameState* state);
	void popState();
	gameState* currentState();

	void handleInput(const std::optional<sf::Event>& event);
	void update();
	void render();
};

class mainMenuState : public gameState{
private:
	sf::RectangleShape menuBackGround;
	std::vector<imageButton*> buttons;
	std::vector<sf::Texture*> icons;
	sf::RenderWindow* win;
	size_t numOfSlide;
public:
	void init(sf::RenderWindow* win) override;
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(Game* game) override;
	void render(sf::RenderWindow* win)override;
	void clean()override;
};

class sapperMenuState : public gameState {
private:
	sf::RectangleShape menuBackGround;
	button* buttonStart, * buttonDifficult, * buttonBack;
	std::string difficults[3];
	unsigned int numOfDifficult;
	sf::RenderWindow* win;
public:
	void init(sf::RenderWindow* win) override;
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(Game* game) override;
	void render(sf::RenderWindow* win)override;
	void clean()override;
};

class sapperGame : public gameState {
private:
	sf::RectangleShape backGround;
	std::vector<std::vector<imageButton*>> cellButtons;
	std::vector<std::vector<int>> typeOfBlock;
	std::vector<std::vector<int>> flagType;
	sf::Vector2f firstClickedMine;
	imageButton* smileButton;
	sf::Texture faceTex;
	sf::Texture facePressTex;
	sf::Texture cellTex;
	sf::Texture cell0to8Tex[9];
	sf::Texture mineTex;
	sf::Texture noMineTex;
	sf::Texture lessMineTex;
	sf::Texture flagTex;
	sf::Texture questionTex;
	sf::Texture counterTex[10];
	sf::Clock animClock;
	sf::Clock gameClock;
	sf::Sprite* counterSprites[6];
	std::string difficults[3];
	int notPressed;
	unsigned int numOfDifficult;
	sf::Vector2f mapSize;
	sf::RenderWindow* win;
	int howManyFlags;
	int howManyTime;
	int mines;
	bool gameStop;
	int gameFlag;
	bool winner ;
	std::string timeCounter, flagCounter;
	void setScreenSize();
	void minesPlace(int mines_count);
	void openCells(int posX, int posY);
	void gameOver(Game* game);
	void gameWin(Game* game);
public:
	sapperGame(unsigned int numOfDifficult);
	void init(sf::RenderWindow* win) override;
	void handleInput(const std::optional<sf::Event>& event) override;
	void update(Game* game) override;
	void render(sf::RenderWindow* win)override;
	void clean()override;
	
};

class sapperPauseMenu : public gameState {
private:
	sf::RenderWindow* win;
	sf::RectangleShape menuBackGround, background;
	button* buttonRestart, * buttonBack, * buttonOut;
	std::function<void(sf::RenderWindow*)> renderFunc;
	int* gameFlag;
public:
	sapperPauseMenu(std::function<void(sf::RenderWindow*)> renderFunc, int* gameFlag);
	~sapperPauseMenu() override;
	void init(sf::RenderWindow* win) override;
	void update(Game* game) override;
	void handleInput(const std::optional<sf::Event>& event) override;
	void render(sf::RenderWindow* win) override;
	void clean() override;
};