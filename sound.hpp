#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Sound_Singleton {
    private:
        static sf::SoundBuffer bombexplosion_b, bombplace_b, battle_theme1_b, battle_theme2_b, powerup_b, menu_theme_b;
        static sf::Sound bombexplosion, bombplace, battle_theme1, battle_theme2, powerup, menu_theme;
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
};
