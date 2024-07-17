#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/SoundBufferRecorder.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <string>
#include<iostream>
#include "mapa.cpp"
#include "mapa.h"
#include "menu.cpp"
#include "animation.cpp"
#include "player.h"

using namespace sf;
using namespace std;

int main() {
    //RenderWindow window(VideoMode::getFullscreenModes()[0], "Bomberman", Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Bomberman");
    window.setVerticalSyncEnabled(true);
    const int WIDTH = window.getSize().x;
    const int HEIGHT = window.getSize().y;
    Mapa_2 mapa(WIDTH, HEIGHT, 5);
    mapa.Print();

    Menu menu;

    bool Game_started = true;

    Clock clock;

    Player_one player(mapa, WIDTH, HEIGHT);
    Player_two player2(mapa);

    while (window.isOpen()) {
        Event event;
        
        //eventos
        while (window.pollEvent(event)) {
            //player.validadMovimiento(mapa.getMatriz());
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                window.close();
        }
        if (!Game_started) {
            menu.handleEvent(window, Game_started);
            menu.draw(window);
            continue;
        }
        float dt = clock.restart().asSeconds();
        window.clear(Color::Black);
        mapa.draw(window);
        player.controlar(mapa, window, dt);
        player2.controlar(mapa, window, dt);
        //player.joystockControl(mapa, window, dt);
        /* player_dos.controlar(mapa); */
        /* player_dos.controlar(); */
        player.draw(window);
        player2.draw(window);
        /* player_dos.draw(window); */
        window.display();
    }
    return EXIT_SUCCESS;
}
