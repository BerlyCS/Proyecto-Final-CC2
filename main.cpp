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
#include "mapa.h"
#include "mapa.cpp"
#include "animation.cpp"
#include "menu.cpp"
#include "animation.h"
#include "player.h"

using namespace sf;
using namespace std;

#define SCREEN_SIZE 600

class Facade_game {
    private:
        sf::RenderWindow window;
        Mapa_2 mapa;
        Menu menu;
        bool Game_started;
        Clock clock;
        Player_one player;
        Player_two player2;
        int WIDTH;
        int HEIGHT;
    public:
        Facade_game() : window(RenderWindow(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Bomberman")), player(mapa, SCREEN_SIZE, SCREEN_SIZE), player2(mapa), mapa(SCREEN_SIZE, SCREEN_SIZE) {
            window.setVerticalSyncEnabled(true);
            mapa.Print();
            Game_started = false;
        }

        bool is_Running() {
            return window.isOpen();
        }

        void update_game() {
            Event event;
            
            //eventos
            while (window.pollEvent(event)) {
                //player.validadMovimiento(mapa.getMatriz());
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == Keyboard::isKeyPressed(Keyboard::Escape)) 
                    Game_started = false;
            }
            if (!Game_started) {
                menu.handleEvent(window, Game_started);
                menu.draw(window);
                return;
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
};

int main() {
    Facade_game game;
    while (game.is_Running()) {
        game.update_game();
    }
    return EXIT_SUCCESS;
}
