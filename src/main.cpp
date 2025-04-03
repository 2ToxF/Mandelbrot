#include <SFML/Graphics.hpp>

const char* const   WINDOW_NAME             = "Mandelbrot graph";

const unsigned int  BITS_PER_PIXEL          = 24;
const unsigned int  WINDOW_HEIGHT           = 600;
const unsigned int  WINDOW_WIDTH            = 600;

const float         DEFAULT_SHIFT_X         = -2.5;
const float         DEFAULT_SHIFT_Y         = -2.0;
const float         DEFAULT_ZOOM            = 4.0;
const float         MOVE_CENTER_COEF        = 0.25;
const float         ZOOM_COEF               = 2.0;
const float         ZOOM_DOWN_SHIFT_COEF    = -0.5;
const float         ZOOM_UP_SHIFT_COEF      = 0.25;

const float         MAX_DISTANCE_QUAD       = 100.0;
const int           MAX_DOT_TRIES           = 256;


int main()
{
    unsigned int window_width   = WINDOW_WIDTH;
    unsigned int window_height  = WINDOW_HEIGHT;
    unsigned int bits_per_pixel = BITS_PER_PIXEL;

    float   x_shift = DEFAULT_SHIFT_X;
    float   y_shift = DEFAULT_SHIFT_Y;
    float   zoom    = DEFAULT_ZOOM;

    sf::Vector2u        window_size (window_width, window_height);
    sf::VideoMode       video_mode  (window_size, bits_per_pixel);
    sf::RenderWindow    window      (video_mode, WINDOW_NAME);

    sf::Image           image       (window_size, sf::Color::White);
    sf::Texture         texture     (window_size);
    sf::Sprite          sprite      (texture);

    while (window.isOpen())
    {
        std::optional event = window.pollEvent();
        while (event)
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            else if (event->is<sf::Event::KeyPressed>())
            {
                const auto* key_pressed = event->getIf<sf::Event::KeyPressed>();

                if (key_pressed->scancode == sf::Keyboard::Scan::Left)
                    x_shift -= MOVE_CENTER_COEF * zoom;
                else if (key_pressed->scancode == sf::Keyboard::Scan::Right)
                    x_shift += MOVE_CENTER_COEF * zoom;
                else if (key_pressed->scancode == sf::Keyboard::Scan::Up)
                    y_shift -= MOVE_CENTER_COEF * zoom;
                else if (key_pressed->scancode == sf::Keyboard::Scan::Down)
                    y_shift += MOVE_CENTER_COEF * zoom;

                else if (key_pressed->scancode == sf::Keyboard::Scan::Equal)
                {
                    x_shift = ZOOM_UP_SHIFT_COEF * zoom + x_shift;
                    y_shift = ZOOM_UP_SHIFT_COEF * zoom + y_shift;
                    zoom /= ZOOM_COEF;
                }
                else if (key_pressed->scancode == sf::Keyboard::Scan::Hyphen)
                {
                    x_shift = ZOOM_DOWN_SHIFT_COEF * zoom + x_shift;
                    y_shift = ZOOM_DOWN_SHIFT_COEF * zoom + y_shift;
                    zoom *= ZOOM_COEF;
                }
            }

            event = window.pollEvent();
        }

        for (unsigned int y = 0; y < window_width; ++y)
        {
            float y0 = (float) y / window_width * zoom + y_shift;
            for (unsigned int x = 0; x < window_height; ++x)
            {
                float x0 = (float) x / window_height * zoom + x_shift;
                // printf("x = %d, y = %d, x0 = %f, y0 = %f\n", x, y, x0, y0);

                float x1 = x0;
                float y1 = y0;

                int n = 0;
                for (; n < MAX_DOT_TRIES; ++n)
                {
                    float x1_quad = x1*x1;
                    float y1_quad = y1*y1;

                    if (x1_quad + y1_quad >= MAX_DISTANCE_QUAD)
                        break;

                    float x1_y1 = x1*y1;
                    x1 = x1_quad - y1_quad + x0;
                    y1 = 2*x1_y1 + y0;
                }

                if (n == MAX_DOT_TRIES)
                    image.setPixel({x, y}, sf::Color::Black);
                else
                    image.setPixel({x, y}, sf::Color(15*n, 0, 255 - 10*n));
            }
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
