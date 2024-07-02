#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation(float frameDuration) : currentFrame(0), frameDuration(frameDuration), elapsedTime(0.0f) {}

    void addFrame(sf::IntRect rect) {
        frames.push_back(rect);
    }

    void applyToSprite(sf::Sprite& sprite) {
        sprite.setTextureRect(frames[currentFrame]);
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
    float frameDuration; // Duración de cada frame en segundos
    float elapsedTime;   // Tiempo transcurrido desde el último cambio de frame
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Sprite");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("images/IMG_20240627_120859.png")) {
        return -1;
    }

    sf::Sprite sprite(texture);

    float frameDuration = 0.3f;
    Animation animation(frameDuration);

    for (int i = 0; i < 3; ++i) {
        animation.addFrame(sf::IntRect(i * 16, 0, 16, 16));
    }
    animation.addFrame(sf::IntRect(16, 0, 16, 16));

    sprite.scale(4, 4);
    sprite.setPosition(400, 300);
    float speed = 100.0f; 

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        bool moving = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-speed * dt, 0);
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(speed * dt, 0);
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite.move(0, -speed * dt);
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite.move(0, speed * dt);
            moving = true;
        }

        if (moving) {
        }
        animation.update(dt);

        animation.applyToSprite(sprite);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
