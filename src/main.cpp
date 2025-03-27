#include <SFML/Graphics.hpp>

const unsigned int  WINDOW_WIDTH    = 600;
const unsigned int  WINDOW_HEIGHT   = 600;
const unsigned int  BITS_PER_PIXEL  = 32;

const char* const   WINDOW_NAME     = "Mandelbrot graph";


int main()
{
    unsigned int window_width   = WINDOW_WIDTH;
    unsigned int window_height  = WINDOW_HEIGHT;
    unsigned int bits_per_pixel = BITS_PER_PIXEL;

    sf::Vector2u        window_size (window_width, window_height);
    sf::VideoMode       video_mode  (window_size, bits_per_pixel);
    sf::RenderWindow    window      (video_mode, WINDOW_NAME);

    sf::Image           image       (window_size, sf::Color::Black);
    sf::Texture         texture     (window_size);
    sf::Sprite          sprite      (texture);

    while (window.isOpen())
    {
        // sf::Event event(sf::Event::Closed);
        // while((event = window.pollEvent()));
        // {
        //     if(event.type == sf::Event::Closed)
        //         window.close();
        // }
        std::optional event = window.pollEvent();
        while (event)
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            event = window.pollEvent();
        }

        for (unsigned int y = 0; y < window_width; ++y)
            for (unsigned int x = 0; x < window_height; ++x)
            {
                image.setPixel({x, y}, sf::Color::Red);
            }

        int text_load_status = texture.loadFromImage(image);
        if (!text_load_status)
            continue;

        sprite.setTexture(texture, true);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
