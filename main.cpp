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
#include "player.h"
#include "sound.hpp"

using namespace sf;
using namespace std;

#define SCREEN_SIZE 1000

class Facade_game {
    private:
        RenderWindow window;
        Mapa_2 mapa;
        Menu menu;
        bool Game_started;
        Clock clock;
        Player_one player;
        Player_two player2;
        int WIDTH;
        int HEIGHT;
    public:
        Facade_game() : window(RenderWindow(sf::VideoMode(SCREEN_SIZE, SCREEN_SIZE), "Bomberman")), player(mapa, SCREEN_SIZE, SCREEN_SIZE), player2(mapa), mapa(SCREEN_SIZE, SCREEN_SIZE), menu(SCREEN_SIZE) {
            window.setVerticalSyncEnabled(true);
            mapa.Print();
            Game_started = true;
            Sound_Singleton::init();//agrega singleton
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
                if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                    Sound_Singleton::stop_battle();
                    Sound_Singleton::play_menu_theme();
                    Game_started = false;
                } 

                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Num1:
                            Sound_Singleton::play_battle_1();
                            break;
                        case sf::Keyboard::Num2:
                            Sound_Singleton::play_battle_2();
                            break;
                        case sf::Keyboard::Num3:
                            Sound_Singleton::play_bombexplosion();
                            break;
                        case sf::Keyboard::Num4:
                            Sound_Singleton::play_bombplace();
                            break;
                        case sf::Keyboard::Num5:
                            Sound_Singleton::play_powerup();
                            break;
                        case sf::Keyboard::Num6:
                            Sound_Singleton::play_menu_theme();
                            break;
                        default:
                            break;
                    }
                }                
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

int main(int argc, char* argv[]) {
    Sound_Singleton::init();
    Facade_game game;
    while (game.is_Running()) {
        game.update_game();
    }
    return EXIT_SUCCESS;
}
