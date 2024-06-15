#include <SFML/Graphics.hpp>

int main() {
    // Crear una ventana de 800x600 píxeles con el título "Ventana SFML"
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ventana SFML");

    // Establecer la velocidad de actualización de la ventana
    window.setFramerateLimit(60);

    // Bucle principal de la aplicación
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            // Cerrar la ventana cuando se recibe el evento de cierre
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Limpiar la ventana con un color negro
        window.clear(sf::Color::Black);

        // Aquí puedes dibujar tus objetos

        // Mostrar el contenido de la ventana
        window.display();
    }

    return 0;
}

