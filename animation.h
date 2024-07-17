#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

class ASprite {
public:
    ASprite(float);
    void addFrame(sf::IntRect rect);

    void applyToSprite(sf::Sprite& sprite);
    void setRects(int start_x, int start_y, int size_x, int size_y, int count);
    void update(float dt);

private:
    std::vector<sf::IntRect> frames;
    size_t currentFrame;
    float frameDuration;
    float elapsedTime;
};

