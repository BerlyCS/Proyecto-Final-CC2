#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "animation.cpp"

class Powerup {
protected:
    ASprite frames;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f pos;

public:
    Powerup() : frames(0.1f) {
        if (!texture.loadFromFile("images/powerups.png")) {
            std::cout<<"Error al cargar images/powerups.png"<<std::endl;
        }
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::Sprite& getSprite() {
        return sprite;
    }

    void updateFrame(float dt) {
        frames.update(dt);
        frames.applyToSprite(sprite);
    }
    void setPos(sf::Vector2f pos) {
        sprite.setPosition(pos);
    }
    void setScale(sf::Vector2f scale) {
        sprite.scale(scale);
    }
};

class FireUpgrade : public Powerup {
public:
    FireUpgrade() : Powerup() {
        for (int i = 0; i < 3; ++i) {
            frames.addFrame(sf::IntRect(i * 16, 0, 16, 16));
        }
        sprite.setPosition(sf::Vector2f(100, 100));
        sprite.setScale(sf::Vector2f(4, 4));
    }
};

class BombUpgrade : public Powerup {
public:
    BombUpgrade() : Powerup() {
        for (int i = 0; i < 3; ++i) {
            frames.addFrame(sf::IntRect(i * 16, 16, 16, 16));
        }
        sprite.setPosition(sf::Vector2f(160, 160));
        sprite.setScale(sf::Vector2f(4, 4));
    }
};

//test
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Sprite");
    window.setFramerateLimit(60);

    FireUpgrade power;
    BombUpgrade power2;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        power.updateFrame(dt);
        power2.updateFrame(dt);

        window.clear(sf::Color::White);
        power.draw(window);
        power2.draw(window);
        window.display();
    }

    return 0;
}
