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
#include "sound.cpp"
#include "sound.hpp"

using namespace sf;

class Button {
private:
    RectangleShape block;
    Text text;
public:
    Button(Vector2f pos, std::string textStr, Font& font, int textSize, int margin = 5) : 
     text(textStr,font,textSize){
         //BOTON
        text.setFillColor(Color::White);
        text.setPosition(pos);

        auto textBounds = text.getLocalBounds();
        block.setSize(Vector2f(textBounds.width+margin*2, textBounds.height+margin*2+26));
        block.setFillColor(Color(100, 100, 100));
        block.setPosition(Vector2f(pos.x-5, pos.y-5));

        /* sound.play(); */
    }

    bool isClicked(RenderWindow& window) {
        Vector2i mousePos = Mouse::getPosition(window);
        if (block.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
            return (Mouse::isButtonPressed(Mouse::Left));
        }
        return false;
    }

    void draw(RenderWindow& window) {
        Vector2i mousePos = Mouse::getPosition(window);
        if (block.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
            block.setFillColor(Color(50,50,50,100));
            /* sound.play(); */
        }
        else {
            block.setFillColor(Color(100,100,100,100));
        }
        window.draw(block);
        window.draw(text);
    }

    String getText() {
        return text.getString();
    }
};

class Menu {
private:
    std::vector<Button> buttons;
    Font font;
    Texture backgroundTexture;
    Sprite backgroundSprite;
public:
    Menu(int SCREEN_SIZE) {
        Sound_Singleton::play_menu_theme();
        if (!font.loadFromFile("font.ttf")) {
            std::cout << "Error al cargar font-ttf" << std::endl;
        }
        if (!backgroundTexture.loadFromFile("images/bg.jpg")) {
            std::cout << "Error al cargar bg" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
        auto size = backgroundTexture.getSize();
        backgroundSprite.scale(float(SCREEN_SIZE)/size.x, float(SCREEN_SIZE)/size.y);

        buttons.push_back(Button(Vector2f(100, 100), "Start", font, 50));
        buttons.push_back(Button(Vector2f(100, 200), "Exit", font, 50));
    }

    void handleEvent(RenderWindow& window, bool& Game_started) {
        for (auto& button : buttons) {
            if (button.isClicked(window)) {
                if (button.getText() == "Start") {
                    Sound_Singleton::stop_menu();
                    srand(10); 
                    rand()%2 ? Sound_Singleton::play_battle_1() : Sound_Singleton::play_battle_2();
                    Game_started = true;
                } else if (button.getText() == "Exit") {
                    window.close();
                }
            }
        }
    }

    void draw(RenderWindow& window) {
        window.clear(); 

        window.draw(backgroundSprite);

        for (auto& button : buttons) {
            button.draw(window);
        }

        window.display();
    }
};

