#include "sound.hpp"
#include <SFML/Audio/Music.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

sf::SoundBuffer Sound_Singleton::bombexplosion_b;
sf::SoundBuffer Sound_Singleton::bombplace_b;
sf::SoundBuffer Sound_Singleton::powerup_b;
sf::Sound Sound_Singleton::bombexplosion;
sf::Sound Sound_Singleton::bombplace;
sf::Music Sound_Singleton::battle_theme1;
sf::Music Sound_Singleton::battle_theme2;
sf::Sound Sound_Singleton::powerup;
sf::Music Sound_Singleton::menu_theme;

void Sound_Singleton::init() {
    if (!bombexplosion_b.loadFromFile("sound/bomb.wav")) {
        std::cerr << "Error al cargar sound/bomb.wav" << std::endl;
    }
    if (!bombplace_b.loadFromFile("sound/place.wav")) {
        std::cerr << "Error al cargar sound/place.wav" << std::endl;
    }
    if (!powerup_b.loadFromFile("sound/powerup.wav")) {
        std::cerr << "Error al cargar sound/powerup.wav" << std::endl;
    }

    if (!menu_theme.openFromFile("sound/menu.ogg")) {
        std::cerr<<"error al cargar menu theme";
    }
    if (!battle_theme1.openFromFile("sound/battle.wav")) {
        std::cerr<<"error al cargar battle theme";
    }
    if (!battle_theme2.openFromFile("sound/battle2.ogg")) {
        std::cerr<<"error al cargar battle2 theme";
    }

    menu_theme.setLoop(true);
    battle_theme1.setLoop(true);
    battle_theme2.setLoop(true);

    menu_theme.setVolume(70.f);
    battle_theme1.setVolume(70.f);
    battle_theme2.setVolume(70.0f);

    bombexplosion.setBuffer(bombexplosion_b);
    bombplace.setBuffer(bombplace_b);
    powerup.setBuffer(powerup_b);
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
