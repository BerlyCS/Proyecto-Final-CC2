#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

const int TILE_SIZE = 32;
const int MAP_WIDTH = 15;
const int MAP_HEIGHT = 15;

class Bomb {
public:
    sf::Sprite sprite;
    sf::Clock timer;
    bool exploded;

    Bomb(sf::Texture& texture, sf::Vector2f position) {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        exploded = false;
    }

    bool isExploded() {
        return timer.getElapsedTime().asSeconds() >= 2.0f;
    }
};

class Player {
public:
    sf::Sprite sprite;
    std::vector<Bomb> bombs;
    sf::Texture& bombTexture;

    Player(sf::Texture& texture, sf::Texture& bombTexture) : bombTexture(bombTexture) {
        sprite.setTexture(texture);
        sprite.setPosition(1 * TILE_SIZE, 1 * TILE_SIZE);
    }

    void handleInput(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::W) sprite.move(0, -TILE_SIZE);
        if (key == sf::Keyboard::S) sprite.move(0, TILE_SIZE);
        if (key == sf::Keyboard::A) sprite.move(-TILE_SIZE, 0);
        if (key == sf::Keyboard::D) sprite.move(TILE_SIZE, 0);
        if (key == sf::Keyboard::Space) placeBomb();
    }

    void placeBomb() {
        sf::Vector2f position = sprite.getPosition();
        position.x = (position.x / TILE_SIZE) * TILE_SIZE;
        position.y = (position.y / TILE_SIZE) * TILE_SIZE;
        bombs.emplace_back(bombTexture, position);
    }

    void updateBombs() {
        for (auto& bomb : bombs) {
            if (bomb.isExploded()) {
                bomb.exploded = true;
            }
        }
        bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Bomb& b) { return b.exploded; }), bombs.end());
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE), "Bomberman");
    window.setFramerateLimit(60);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("player.png");

    sf::Texture bombTexture;
    bombTexture.loadFromFile("bomb.png");

    Player player(playerTexture, bombTexture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                player.handleInput(event.key.code);
        }

        player.updateBombs();

        window.clear();

        window.draw(player.sprite);
        for (auto& bomb : player.bombs) {
            window.draw(bomb.sprite);
        }

        window.display();
    }

    return 0;
}

