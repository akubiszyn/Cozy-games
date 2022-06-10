//#include <box2d/box2d.h>
#include "Menu.h"
#include "Game.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "PROI GAME", sf::Style::Fullscreen);

    Menu menu(window);
    int highscore_on = 0;
    Game game(window, 30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (highscore_on == 0)
            {
                switch (event.type)
                {
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (menu.getPressedItem())
                        {
                        case 0:
                            std::cout << "Game starts" << std::endl;
                            while (game.get_is_end() == false)
                            {
                                game.update_game();
                            }

                            break;
                        case 1:
                            window.close();
                            break;
                        }
                        break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }
        }



        if (highscore_on == 1)
        {
            window.clear();
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                highscore_on = 0;
                menu.MoveUp();
            }
        }
        else
        {
            window.clear();
            menu.draw(window);
            window.display();
        }



    }
    return 0;
}
