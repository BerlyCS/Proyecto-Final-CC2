#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Sound_Singleton {
    private:
        static sf::SoundBuffer bombexplosion_b, bombplace_b, battle_theme1_b, battle_theme2_b, powerup_b, menu_theme_b;
        static sf::Sound bombexplosion, bombplace, battle_theme1, battle_theme2, powerup, menu_theme;
        Sound_Singleton() = default;

    public:
        static void init() {
            if (!battle_theme1_b.loadFromFile("sound/battle.wav")) {
                std::cerr << "Error al cargar sound/battle.wav" << std::endl;
            }
            if (!battle_theme2_b.loadFromFile("sound/battle2.ogg")) {
                std::cerr << "Error al cargar sound/battle2.ogg" << std::endl;
            }
            if (!bombexplosion_b.loadFromFile("sound/bomb.wav")) {
                std::cerr << "Error al cargar sound/bomb.wav" << std::endl;
            }
            if (!bombplace_b.loadFromFile("sound/place.wav")) {
                std::cerr << "Error al cargar sound/place.wav" << std::endl;
            }
            if (!powerup_b.loadFromFile("sound/powerup.wav")) {
                std::cerr << "Error al cargar sound/powerup.wav" << std::endl;
            }
            if (!menu_theme_b.loadFromFile("sound/menu.ogg")) {
                std::cerr << "Error al cargar sound/menu.ogg" << std::endl;
            }

            battle_theme1.setBuffer(battle_theme1_b);
            battle_theme2.setBuffer(battle_theme2_b);
            bombexplosion.setBuffer(bombexplosion_b);
            bombplace.setBuffer(bombplace_b);
            powerup.setBuffer(powerup_b);
            menu_theme.setBuffer(menu_theme_b);
        }

        static void play_battle_1() {
            battle_theme1.play();
        }

        static void play_battle_2() {
            battle_theme2.play();
        }

        static void play_bombexplosion() {
            bombexplosion.play();
        }

        static void play_bombplace() {
            bombplace.play();
        }

        static void play_powerup() {
            powerup.play();
        }

        static void play_menu_theme() {
            menu_theme.play();
        }
};

sf::SoundBuffer Sound_Singleton::bombexplosion_b;
sf::SoundBuffer Sound_Singleton::bombplace_b;
sf::SoundBuffer Sound_Singleton::battle_theme1_b;
sf::SoundBuffer Sound_Singleton::battle_theme2_b;
sf::SoundBuffer Sound_Singleton::powerup_b;
sf::SoundBuffer Sound_Singleton::menu_theme_b;
sf::Sound Sound_Singleton::bombexplosion;
sf::Sound Sound_Singleton::bombplace;
sf::Sound Sound_Singleton::battle_theme1;
sf::Sound Sound_Singleton::battle_theme2;
sf::Sound Sound_Singleton::powerup;
sf::Sound Sound_Singleton::menu_theme;
 
 //test content
 /*
int main() {
    Sound_Singleton::init(); //iniciar

    sf::RenderWindow window(sf::VideoMode(800, 600), "Sound Test");

    while (window.isOpen()) { //event manager
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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

        window.clear();
        // Aquí puedes dibujar cosas si es necesario
        window.display();
    }

    return 0;
}
*/
