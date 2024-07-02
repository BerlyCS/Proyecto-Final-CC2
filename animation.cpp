#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

class ASprite {
public:
    ASprite(float frameDuration) : currentFrame(0), frameDuration(frameDuration), elapsedTime(0.0f) {}

    void addFrame(sf::IntRect rect) {
        frames.push_back(rect);
    }

    void applyToSprite(sf::Sprite& sprite) {
        sprite.setTextureRect(frames[currentFrame]);
    }

    void setRects(int start_x, int start_y, int size_x, int size_y, int count) {
        //Para seleccionar automaticamente las areas
        //necesarias en las texturas de forma continua
        for (int i=0; i<count; i++) {
            addFrame(sf::IntRect(i*size_x+start_x, start_y, size_x, size_y));
        }
    }

    void update(float dt) {
        elapsedTime += dt;
        if (elapsedTime >= frameDuration) {
            elapsedTime = 0.0f;
            currentFrame = (currentFrame + 1) % frames.size();
        }
    }

private:
    std::vector<sf::IntRect> frames;
    size_t currentFrame;
    float frameDuration;
    float elapsedTime;
};

