#include "Game.h"

using namespace sf;

int main()
{
    RenderWindow win(VideoMode({ 715, 455 }), "Game Center", Style::Close);
    Game game(&win);
    game.pushState(new mainMenuState());
    while (win.isOpen())
    {
        while (const std::optional event = win.pollEvent())
        {
            if (event->is<Event::Closed>())
                win.close();
            game.handleInput(event);
        }

        game.update();

        win.clear();
        game.render();
        win.display();
    }
}