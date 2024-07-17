#include "animation.h"

ASprite::ASprite(float frameDuration) : currentFrame(0), frameDuration(frameDuration), elapsedTime(0.0f) {}

void ASprite::addFrame(sf::IntRect rect) {
    frames.push_back(rect);
}

void ASprite::applyToSprite(sf::Sprite& sprite) {
    sprite.setTextureRect(frames[currentFrame]);
}

void ASprite::setRects(int start_x, int start_y, int size_x, int size_y, int count) {
    //Para seleccionar automaticamente las areas
    //necesarias en las texturas de forma continua
    for (int i=0; i<count; i++) {
        addFrame(sf::IntRect(i*size_x+start_x, start_y, size_x, size_y));
    }
}

void ASprite::update(float dt) {
    elapsedTime += dt;
    if (elapsedTime >= frameDuration) {
        elapsedTime = 0.0f;
        currentFrame = (currentFrame + 1) % frames.size();
    }
}


