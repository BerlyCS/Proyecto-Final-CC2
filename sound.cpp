#include "sound.hpp"
#include <cstdlib>
#include <ctime>

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

void Sound_Singleton::init() {
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

void Sound_Singleton::play_battle_1() {
    battle_theme1.play();
}

void Sound_Singleton::play_battle_2() {
    battle_theme2.play();
}

void Sound_Singleton::play_rand_battle() {
    srand(time(nullptr));
    rand()%2 ? battle_theme1.play() : battle_theme2.play();
}

void Sound_Singleton::play_bombexplosion() {
    bombexplosion.play();
}

void Sound_Singleton::play_bombplace() {
    bombplace.play();
}

void Sound_Singleton::play_powerup() {
    powerup.play();
}

void Sound_Singleton::play_menu_theme() {
    menu_theme.play();
}

void Sound_Singleton::stop_menu() {
    menu_theme.stop();
}

void Sound_Singleton::stop_battle() {
    battle_theme1.stop();
    battle_theme2.stop();
}
