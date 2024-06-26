#include <SFML/Graphics.hpp>

int main()
{
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Cargar una textura (imagen)
    sf::Texture texture;
    if (!texture.loadFromFile("images/wall.png"))
    {
        // Manejar error
        return -1;
    }

    // Crear un sprite con la textura cargada
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Bucle principal
    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el sprite
        window.draw(sprite);

        // Mostrar lo dibujado en la ventana
        window.display();
    }

    return 0;
}
