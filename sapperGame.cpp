#include"Game.h"

using namespace sf;


void sapperGame::setScreenSize() {
	win->setSize(Vector2u(400, 460));
}
void sapperGame::minesPlace(int mines_count) {
	
	for (size_t i = 0; i < mapSize.y; ++i) {
		for (size_t j = 0; j < mapSize.x; ++j) {
			cellButtons[i][j]->setTexture(cellTex);
			typeOfBlock[i][j] = 0;
			flagType[i][j] = 1;
		}
	}

	int newX, newY;
	std::vector<Vector2f> minesPos;
	std::random_device rd;
	std::mt19937 gen(rd());
	int width = mapSize.x - 1;
	int height = mapSize.y - 1;
	std::uniform_int_distribution<> distribX(0, width);
	std::uniform_int_distribution<> distribY(0, height);
	Vector2f randomCell;
	for (int i = 0; i < mines_count; ++i) {
		randomCell.x = distribX(gen);
		randomCell.y = distribY(gen);
		for (int j = 0; j < minesPos.size(); ++j) {
			if ((randomCell.x == minesPos[j].x) && (randomCell.y == minesPos[j].y)) {
				randomCell.x = distribX(gen);
				randomCell.y = distribY(gen);
				j = -1;
			}
		}
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (dx == 0 && dy == 0) continue;
				int nx = randomCell.x + dx;
				int ny = randomCell.y + dy;
				if (nx >= 0 && nx <= width && ny >= 0 && ny <= height) {
					if (typeOfBlock[ny][nx] != 9)
						typeOfBlock[ny][nx]++;
				}
			}
		}
		minesPos.push_back(randomCell);
		typeOfBlock[minesPos[i].y][minesPos[i].x] = 9;
	}
}
void sapperGame::openCells(int posX, int posY) {
	

	int width = mapSize.x - 1;
	int height = mapSize.y - 1;

	if (flagType[posY][posX] != 1) return;

	flagType[posY][posX] = 0;
	cellButtons[posY][posX]->setTexture(cell0to8Tex[typeOfBlock[posY][posX]]);

	if (typeOfBlock[posY][posX] != 0) return;
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			if (dx == 0 && dy == 0) continue;
			int nx = posX + dx;
			int ny = posY + dy;
			if (nx >= 0 && nx <= width && ny >= 0 && ny <= height) {
					openCells(nx, ny);
			}
		}
	}
}

void sapperGame::gameOver(Game* game) {
	
	gameStop = 1;
	

}

void sapperGame::gameWin(Game * game) {

}

sapperGame::sapperGame(unsigned int numOfDifficult) {
	this->numOfDifficult = numOfDifficult;
}
void sapperGame::init(sf::RenderWindow* win) {
	this->win = win;
	howManyFlags = 0;
	gameStop = 0;
	gameFlag = 0;
	notPressed = 0;
	winner = 0;
	animClock.reset();
	gameClock.reset();
	switch (numOfDifficult) {
	case 0:
		win->create(VideoMode({ 400, 460 }), "Sapper", Style::Close);
		break;
	case 1:
		win->create(VideoMode({ 520, 580 }), "Sapper", Style::Close);
		break;
	case 2:
		win->create(VideoMode({ 940, 580 }), "Sapper", Style::Close);
		break;
	}

	backGround.setSize(Vector2f(win->getSize().x, win->getSize().y));
	backGround.setFillColor(Color(157, 157, 157));
	backGround.setPosition(Vector2f(0, 0));

	cell0to8Tex[0].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {0,32},{16,16 } });
	cell0to8Tex[1].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {0,0},{16,16 } });
	cell0to8Tex[2].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {16,0},{16,16 } });
	cell0to8Tex[3].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {32,0},{16,16 } });
	cell0to8Tex[4].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {48,0},{16,16 } });
	cell0to8Tex[5].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {0,16},{16,16 } });
	cell0to8Tex[6].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {16,16},{16,16 } });
	cell0to8Tex[7].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {32,16},{16,16 } });
	cell0to8Tex[8].loadFromFile("Textures/sapperTex/sapperCells.png", false, { {48,16},{16,16 } });

	mineTex.loadFromFile("Textures/sapperTex/sapperCells.png", false, { {32,48},{16,16 } });
	noMineTex.loadFromFile("Textures/sapperTex/sapperCells.png", false, { {48,32},{16,16 } });
	lessMineTex.loadFromFile("Textures/sapperTex/sapperCells.png", false, { {48,48},{16,16 } });
	cellTex.loadFromFile("Textures/sapperTex/sapperCells.png", false, { {16,32},{16,16 } });
	flagTex.loadFromFile("Textures/sapperTex/sapperCells.png", false, { {32,32},{16,16 } });
	questionTex.loadFromFile("Textures/sapperTex/sapperCells.png", false, { {16,48},{16,16 } });

	faceTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {0,0},{52,52} });
	facePressTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {0,52},{52,52} });

	int numOfCounter = 0;
	for (int i = 0;i < 2;++i) {
		for (int j = 0;j < 5;++j) {
			counterTex[numOfCounter].loadFromFile("Textures/sapperTex/allCounters.png", false, { {j * 65,i * 115},{65,115} });
			++numOfCounter;
		}
	}

	Vector2f counterNewScale = Vector2f(29.4/65, 52.0/115);
	for (int i = 0;i < 6;++i) {
		counterSprites[i] = new Sprite(counterTex[0]);
		counterSprites[i]->setScale(counterNewScale);
	}

	switch (numOfDifficult) {
	case 0:
		mines = 10;
		mapSize.x = 9;
		mapSize.y = 9;
		smileButton = new imageButton(Vector2f(174, 14), Vector2f(52,52), faceTex);

		counterSprites[0]->setPosition(Vector2f(36.9, 14));
		counterSprites[1]->setPosition(Vector2f(66.3,14));
		counterSprites[2]->setPosition(Vector2f(95.7, 14));

		counterSprites[3]->setPosition(Vector2f(274.9, 14));
		counterSprites[4]->setPosition(Vector2f(304.3, 14));
		counterSprites[5]->setPosition(Vector2f(333.7, 14));

		cellButtons.resize(9);
		typeOfBlock.resize(9);
		flagType.resize(9);
		for (size_t i = 0; i < 9; ++i) {
			cellButtons[i].resize(9);
			typeOfBlock[i].resize(9);
			flagType[i].resize(9);
			for (size_t j = 0; j < 9; ++j) {
				cellButtons[i][j] = new imageButton(Vector2f(j * 40 + 20, i * 40 + 80), Vector2f(40, 40), cellTex);
				typeOfBlock[i][j] = 0;
				flagType[i][j] = 1;
			}
		}
		minesPlace(mines);
		break;
	case 1:
		mines = 40;
		mapSize.x = 16;
		mapSize.y = 16;
		smileButton = new imageButton(Vector2f(234, 14), Vector2f(52, 52), faceTex);

		counterSprites[0]->setPosition(Vector2f(32.9, 14));
		counterSprites[1]->setPosition(Vector2f(62.3, 14));
		counterSprites[2]->setPosition(Vector2f(91.7, 14));

		counterSprites[3]->setPosition(Vector2f(399.9, 14));
		counterSprites[4]->setPosition(Vector2f(428.3, 14));
		counterSprites[5]->setPosition(Vector2f(457.7, 14));

		cellButtons.resize(16);
		typeOfBlock.resize(16);
		flagType.resize(16);
		for (size_t i = 0; i < 16; ++i) {
			cellButtons[i].resize(16);
			typeOfBlock[i].resize(16);
			flagType[i].resize(16);
			for (size_t j = 0; j < 16; ++j) {
				cellButtons[i][j] = new imageButton(Vector2f(j * 30 + 20, i * 30 + 80), Vector2f(30, 30), cellTex);
				typeOfBlock[i][j] = 0;
				flagType[i][j] = 1;
			}
		}
		minesPlace(mines);
		break;
	case 2:
		mines = 99;
		mapSize.x = 30;
		mapSize.y = 16;
		smileButton = new imageButton(Vector2f(444, 14), Vector2f(52, 52), faceTex);

		counterSprites[0]->setPosition(Vector2f(32.9, 14));
		counterSprites[1]->setPosition(Vector2f(62.3, 14));
		counterSprites[2]->setPosition(Vector2f(91.7, 14));

		counterSprites[3]->setPosition(Vector2f(818.9, 14));
		counterSprites[4]->setPosition(Vector2f(848.3, 14));
		counterSprites[5]->setPosition(Vector2f(877.7, 14));

		cellButtons.resize(16);
		typeOfBlock.resize(16);
		flagType.resize(16);
		for (size_t i = 0; i < 16; ++i) {
			cellButtons[i].resize(30);
			typeOfBlock[i].resize(30);
			flagType[i].resize(30);
			for (size_t j = 0; j < 30; ++j) {
				cellButtons[i][j] = new imageButton(Vector2f(j * 30 + 20, i * 30 + 80), Vector2f(30, 30), cellTex);
				typeOfBlock[i][j] = 0;
				flagType[i][j] = 1;
			}
		}
		minesPlace(mines);
		break;
	}
} 
void sapperGame::handleInput(const std::optional<sf::Event>& event) {
	for (size_t i = 0; i < mapSize.y; ++i) {
		for (size_t j = 0; j < mapSize.x; ++j) {
			cellButtons[i][j]->clickHandle(win, event);
		}
	}
	smileButton->clickHandle(win, event);
}
void sapperGame::update(Game* game) {
	if ((gameClock.getElapsedTime().asSeconds() > 0) && (!gameStop))
		gameClock.start();
	howManyTime = gameClock.getElapsedTime().asSeconds();
	if (howManyTime < 10) {
		timeCounter = "00" + std::to_string(howManyTime);
	}
	else if (howManyTime < 100) {
		timeCounter = "0" + std::to_string(howManyTime);
	}
	else if (howManyTime < 1000) {
		timeCounter = std::to_string(howManyTime);
	}
	else {
		howManyTime = 999;
		gameClock.restart();
	}

	if (mines - howManyFlags < 10) {
		flagCounter = "00" + std::to_string(mines - howManyFlags);
	}
	else if (mines - howManyFlags < 100) {
		flagCounter = "0" + std::to_string(mines - howManyFlags);
	}
	else if (mines - howManyFlags < 1000) {
		flagCounter = std::to_string(mines - howManyFlags);
	}

	counterSprites[0]->setTexture(counterTex[timeCounter[0]-'0']);
	counterSprites[1]->setTexture(counterTex[timeCounter[1] - '0']);
	counterSprites[2]->setTexture(counterTex[timeCounter[2] - '0']);

	counterSprites[3]->setTexture(counterTex[flagCounter[0] - '0']);
	counterSprites[4]->setTexture(counterTex[flagCounter[1] - '0']);
	counterSprites[5]->setTexture(counterTex[flagCounter[2] - '0']);

	if(!gameStop)
	{
		for (size_t i = 0; i < mapSize.y; ++i) {
			if (gameFlag)break;
			for (size_t j = 0; j < mapSize.x; ++j) {
				if (gameFlag)break;
				if (cellButtons[i][j]->isClickedLeft()) {
					if (!gameClock.isRunning())
						gameClock.start();
					if ((typeOfBlock[i][j] == 9) && (flagType[i][j] == 1)) {
						cellButtons[i][j]->setTexture(lessMineTex);
						firstClickedMine = Vector2f(j, i);
						gameOver(game);
						gameClock.stop();
						faceTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {104,0},{52,52} });
						facePressTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {104,52},{52,52} });
						if (gameFlag)break;
					}
					else if (flagType[i][j] == 1) {
						openCells(j, i);

					}
				}
				else if ((cellButtons[i][j]->isClickedRight()) && flagType[i][j]) {
					if (!gameClock.isRunning())
						gameClock.start();
					if (flagType[i][j] == 3)
						flagType[i][j] = 1;
					else if ((howManyFlags < mines) || flagType[i][j] == 2)
						++flagType[i][j];
					if (flagType[i][j] == 1)
						cellButtons[i][j]->setTexture(cellTex);
					if (flagType[i][j] == 2 && (howManyFlags < mines))
					{
						cellButtons[i][j]->setTexture(flagTex);
						++howManyFlags;
					}
					if (flagType[i][j] == 3)
					{
						cellButtons[i][j]->setTexture(questionTex);
						--howManyFlags;
					}
					cellButtons[i][j]->dropClick();
				}
				if (flagType[i][j])
					++notPressed;
			}
		}
		if (notPressed == mines)
		{
			faceTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {52,0},{52,52} });
			facePressTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {52,52},{52,52} });
			winner = 1;
			gameStop = 1;
		}
		notPressed = 0;
	}
	else {
		gameClock.stop();
		for (size_t i = 0; i < mapSize.y; ++i) {
			for (size_t j = 0; j < mapSize.x; ++j) {
				if ((typeOfBlock[i][j] != 9) && (flagType[i][j] == 2)) {
					cellButtons[i][j]->setTexture(noMineTex);
				}
				if ((typeOfBlock[i][j] == 9) && (flagType[i][j] == 1)) {
					flagType[i][j] = 0;
					cellButtons[i][j]->setTexture(mineTex);
					i = mapSize.y;
					break;
				}
			}
		}
		if(!winner)
			cellButtons[firstClickedMine.y][firstClickedMine.x]->setTexture(lessMineTex);
	}
	
	if (smileButton->isClickedLeft()) {
		smileButton->setTexture(facePressTex);
		
		animClock.start();
	}
	else if(animClock.getElapsedTime().asMilliseconds()>130) {
		smileButton->setTexture(faceTex);
		animClock.reset();
		smileButton->dropClick();
		gameClock.stop();
		game->pushState(new sapperPauseMenu([this](RenderWindow* win) {this->render(win);}, &gameFlag));
		return;
	}
	if (gameFlag == 1) {
		faceTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {0,0},{52,52} });
		facePressTex.loadFromFile("Textures/sapperTex/winFaces.png", false, { {0,52},{52,52} });
		minesPlace(mines);
		gameFlag = 0;
		howManyFlags = 0;
		timeCounter = "000";
		gameStop = 0;
		winner = 0;
		gameClock.reset();
	}
	if (gameFlag == 2) {
		win->create(VideoMode({ 715, 455 }), "Sapper", Style::Close);
		game->popState();
	}
}
void sapperGame::render(sf::RenderWindow* win) {
	win->draw(backGround);
	for (size_t i = 0; i < cellButtons.size(); ++i) {
		for (size_t j = 0; j < cellButtons[i].size(); ++j) {
			cellButtons[i][j]->draw(win);
		}
	}
	smileButton->draw(win);
	for (size_t i = 0;i < 6;++i) {
		win->draw(*counterSprites[i]);
	}
}
void sapperGame::clean() {
	delete smileButton;
	for (auto& row : cellButtons) {
		for (auto ptr : row) {
			delete ptr;
		}
		row.clear();
	}
	for (auto ptr : counterSprites)
		delete ptr;

	cellButtons.clear();
}

