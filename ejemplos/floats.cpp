#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Float Movement");
    window.setFramerateLimit(60);
    sf::CircleShape shape(50);
    shape.setFillColor(sf::Color::Green);
    float x = 0.0f;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = clock.restart();
        x += 100.0f * deltaTime.asSeconds(); // Move by 100 pixels per second
        shape.setPosition(x, 300);

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

