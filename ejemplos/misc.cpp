#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear una ventana de 800x600 píxeles con el título "Ventana SFML"
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ventana SFML");

    // Establecer la velocidad de actualización de la ventana
    window.setFramerateLimit(60);

    // Crear un círculo
    sf::CircleShape circle(50); // Radio de 50 píxeles
    circle.setFillColor(sf::Color::Green); // Color verde
    circle.setPosition(100, 100); // Posición en la ventana

    // Crear un rectángulo
    sf::RectangleShape rectangle(sf::Vector2f(120, 60)); // Tamaño 120x60 píxeles
    rectangle.setFillColor(sf::Color::Blue); // Color azul
    rectangle.setPosition(300, 200); // Posición en la ventana

    // Bucle principal de la aplicación
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cerrar la ventana cuando se recibe el evento de cierre
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Detectar teclas
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close(); // Cerrar la ventana al presionar Escape
                } else if (event.key.code == sf::Keyboard::Up) {
                    circle.move(0, -10); // Mover el círculo hacia arriba
                } else if (event.key.code == sf::Keyboard::Down) {
                    circle.move(0, 10); // Mover el círculo hacia abajo
                } else if (event.key.code == sf::Keyboard::Left) {
                    circle.move(-10, 0); // Mover el círculo hacia la izquierda
                } else if (event.key.code == sf::Keyboard::Right) {
                    circle.move(10, 0); // Mover el círculo hacia la derecha
                }
            }

            // Detectar clic del ratón
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked at: " << mousePosition.x << ", " << mousePosition.y << std::endl;
                }
            }
        }

        // Limpiar la ventana con un color negro
        window.clear(sf::Color::Black);

        // Dibujar el círculo y el rectángulo
        window.draw(circle);
        window.draw(rectangle);

        // Mostrar el contenido de la ventana
        window.display();
    }

    return 0;
}

