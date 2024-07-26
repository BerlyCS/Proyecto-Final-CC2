#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Sound_Singleton {
    private:
        static sf::SoundBuffer bombexplosion_b, bombplace_b, powerup_b;
        static sf::Sound bombexplosion, bombplace, powerup;
        static sf::Music battle_theme1, battle_theme2, menu_theme;
        Sound_Singleton() = default;

    public:
        static void init();
        static void play_battle_1();
        static void play_battle_2();
        static void play_bombexplosion();
        static void play_rand_battle();
        static void play_bombplace();
        static void play_powerup();
        static void play_menu_theme();
        static void stop_menu();
        static void stop_battle();
        static bool is_playing_theme();
};
