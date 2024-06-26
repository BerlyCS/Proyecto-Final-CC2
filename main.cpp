#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include "mapa.cpp"

using namespace sf;
using namespace std;

class player {
    protected:
        Texture images[4];
        Sprite sprite;
        double x,y, speed;
        int bombcount;
    public:
        player() {
            speed = 1.0f;
            bombcount = 1;
        }

        void manejarEvento(const sf::Event& evento)
        {
            if (evento.type == sf::Event::KeyPressed)
            {
                if (evento.key.code == sf::Keyboard::Up)
                {
                    sprite.move(0, -5.0f);
                    sprite.setTexture(images[0]);
                }
                else if (evento.key.code == sf::Keyboard::Down)
                {
                    sprite.move(0, 5.0f);
                    sprite.setTexture(images[2]);                }
                else if (evento.key.code == sf::Keyboard::Left)
                {
                    sprite.move(-5.0f, 0);
                    sprite.setTexture(images[1]);                }
                else if (evento.key.code == sf::Keyboard::Right)
                {
                    sprite.move(5.0f, 0);
                    sprite.setTexture(images[3]);                }
            }
        }
        void draw(RenderWindow& win) {
            win.draw(sprite);
        }

};

class player_one : public player {
    public:
        player_one() : player() {
            sprite.setPosition(Vector2f(100,100));
            images[0].loadFromFile("images/Character_W_4.png");
            images[1].loadFromFile("images/Character_A_4.png");
            images[2].loadFromFile("images/Character_S_4.png");
            images[3].loadFromFile("images/Character_D_4.png");
        }
};

int main() {

    RenderWindow window(VideoMode::getFullscreenModes()[0], "Bouncing balls", Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    mapa map(WIDTH, HEIGHT);
    map.print_layout();
    player_one player;

    /* Font font; */
    /* if (!font.loadFromFile("pixelated.ttf")) { */

    /*     return EXIT_FAILURE; */
    /* } */

    while (window.isOpen()) {
        Event event;
        //Eventos
        while (window.pollEvent(event)) {
            player.manejarEvento(event);
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();            
            
        }
        window.clear(Color::Cyan);
        player.draw(window);
        /* map.draw(window); */
        window.display();
        //logica aqui
    }
    return EXIT_SUCCESS;
}
