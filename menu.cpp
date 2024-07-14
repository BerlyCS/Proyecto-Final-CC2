#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

using namespace sf;

class Button {
private:
    RectangleShape block;
    Text text;
    SoundBuffer buffer;
    Sound sound;
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

        buffer.loadFromFile("2.wav");
        sound.setBuffer(buffer);
        sound.play();
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
            block.setFillColor(Color(50,50,50));
            sound.play();
        }
        else {
            block.setFillColor(Color(100,100,100));
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
public:
    Menu() {
        if (!font.loadFromFile("font.ttf")) {
            std::cout<<"Error al cargar la fuente"<<std::endl;
        }
        buttons.push_back(Button(Vector2f(100, 100), "Start", font, 40));
        buttons.push_back(Button(Vector2f(100, 200), "Exit", font, 40));
    }

    void handleEvent(RenderWindow& window, bool& Game_started) {
        for (auto& button : buttons) {
            if (button.isClicked(window)) {
                if (button.getText() == "Start") {
                    Game_started = true;
                } else if (button.getText() == "Exit") {
                    window.close();
                }
            }
        }
    }

    void draw(RenderWindow& window) {
        for (auto& button : buttons) {
            button.draw(window);
            window.display();
        }
    }
};

/* int main() { */
/*     // Crear una ventana */
/*     sf::RenderWindow window(sf::VideoMode(800, 600), "Imprimir Texto en SFML"); */
/*     window.setFramerateLimit(60); */

/*     Menu menu; */

/*     while (window.isOpen()) { */
/*         sf::Event event; */
/*         while (window.pollEvent(event)) { */
/*             if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { */
/*                 window.close(); */
/*             } */
/*         } */

/*         menu.handleEvent(window); */

/*         window.clear(); // Limpiar la ventana */
/*         menu.draw(window); */
/*         window.display(); // Mostrar el contenido en la ventana */
/*     } */

/*     return 0; */
/* } */
