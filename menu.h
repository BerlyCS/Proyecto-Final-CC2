#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdlib>
#include <iostream>
#include "sound.hpp"

using namespace sf;

class Button {
private:
    RectangleShape block;
    Text text;
public:
    Button(Vector2f pos, std::string textStr, Font& font, int textSize, int margin); 
    bool isClicked(RenderWindow& window); 
    void draw(RenderWindow& window);
    String getText();
};

class Menu {
private:
    std::vector<Button> buttons;
    Font font;
    Texture backgroundTexture;
    Sprite backgroundSprite;
public:
    Menu(int SCREEN_SIZE); 
    void handleEvent(RenderWindow& window, bool& Game_started);
    void draw(RenderWindow& window);
};

