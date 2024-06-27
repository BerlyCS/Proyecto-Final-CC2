#include <SFML/Graphics.hpp>
#include <vector>


class Animation {
public:
    Animation() : currentFrame(0) {}

    void addFrame(sf::IntRect rect) {
        frames.push_back(rect);
    }

    void applyToSprite(sf::Sprite& sprite) {
        sprite.setTextureRect(frames[currentFrame]);
    }

    void update() {
        currentFrame = (currentFrame + 1) % frames.size();
    }

private:
    std::vector<sf::IntRect> frames;
    size_t currentFrame;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Animated Sprite");

    sf::Texture texture;
    if (!texture.loadFromFile("images/Character_A_4.png")) {
        return -1; // Error al cargar la textura
    }

    sf::Sprite sprite(texture);

    Animation animation;
    // Añadir frames de la animación (asumiendo cada frame es de 32x32 píxeles)
    for (int i = 0; i < 3; ++i) {
        animation.addFrame(sf::IntRect(i * 32, 0, 32, 32));
    }

    sprite.setPosition(400, 300);
    float speed = 100.0f; // Velocidad de movimiento en píxeles por segundo

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            sprite.move(-speed * dt, 0);
            animation.update();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            sprite.move(speed * dt, 0);
            animation.update();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            sprite.move(0, -speed * dt);
            animation.update();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            sprite.move(0, speed * dt);
            animation.update();
        }

        animation.applyToSprite(sprite);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
