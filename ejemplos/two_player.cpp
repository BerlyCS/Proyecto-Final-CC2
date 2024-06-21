#include <SFML/Graphics.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <chrono>

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Two Player Control");

    // Define two squares
    sf::RectangleShape square1(sf::Vector2f(50.0f, 50.0f));
    square1.setFillColor(sf::Color::Red);
    square1.setPosition(100.0f, 100.0f);

    sf::RectangleShape square2(sf::Vector2f(50.0f, 50.0f));
    square2.setFillColor(sf::Color::Blue);
    square2.setPosition(200.0f, 100.0f);

    // Speed of the squares
    float squareSpeed = 0.1f;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle player 1 movement (WASD)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            square1.move(0.0f, -squareSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            square1.move(0.0f, squareSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            square1.move(-squareSpeed, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            square1.move(squareSpeed, 0.0f);
        }

        // Handle player 2 movement (Arrow keys)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            square2.move(0.0f, -squareSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            square2.move(0.0f, squareSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            square2.move(-squareSpeed, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            square2.move(squareSpeed, 0.0f);
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw the squares
        window.draw(square1);
        window.draw(square2);
        sf::sleep(sf::Time());
        // Display the contents of the window
        window.display();
    }

    return 0;
}

