#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <sys/time.h>

#include "global_consts.h"
#include "mandelbrot.h"
#include "window.h"

const char* const   WINDOW_NAME             = "Mandelbrot graph";

const unsigned int  BITS_PER_PIXEL          = 24;

const float         MOVE_CENTER_COEF        = 0.25;
const float         ZOOM_COEF               = 2.0;
const float         ZOOM_DOWN_SHIFT_COEF    = -0.5;
const float         ZOOM_UP_SHIFT_COEF      = 0.25;

const int           MICROSEC_TO_SEC         = 1000000;

static void     CheckEvents         (sf::RenderWindow* window, MandelbrotInfo* data);
static void     DrawDots            (sf::Image* image, int* arr_iters);
static double   GetMandelbrotTime   (MandelbrotInfo* data, void (*CalcMandelbrotFunc)(MandelbrotInfo* data));
static void     ZoomDown            (MandelbrotInfo* data);
static void     ZoomUp              (MandelbrotInfo* data);


static void CheckEvents(sf::RenderWindow* window, MandelbrotInfo* data)
{
    std::optional event = window->pollEvent();
    while (event)
    {
        if (event->is<sf::Event::Closed>())
            window->close();

        else if (event->is<sf::Event::KeyPressed>())
        {
            const auto* key_pressed = event->getIf<sf::Event::KeyPressed>();

            if (key_pressed->scancode == sf::Keyboard::Scan::Left)
                data->x_shift -= MOVE_CENTER_COEF * data->zoom;
            else if (key_pressed->scancode == sf::Keyboard::Scan::Right)
                data->x_shift += MOVE_CENTER_COEF * data->zoom;
            else if (key_pressed->scancode == sf::Keyboard::Scan::Up)
                data->y_shift -= MOVE_CENTER_COEF * data->zoom;
            else if (key_pressed->scancode == sf::Keyboard::Scan::Down)
                data->y_shift += MOVE_CENTER_COEF * data->zoom;

            else if (key_pressed->scancode == sf::Keyboard::Scan::Equal)
                ZoomUp(data);
            else if (key_pressed->scancode == sf::Keyboard::Scan::Hyphen)
                ZoomDown(data);
        }

        event = window->pollEvent();
    }
}


static void DrawDots(sf::Image* image, int* arr_iters)
{
    for (unsigned int y = 0; y < WINDOW_WIDTH; ++y)
    {
        for (unsigned int x = 0; x < WINDOW_HEIGHT; ++x)
        {
            int n = *(arr_iters + y*WINDOW_WIDTH + x);
            if (n == MAX_DOT_TRIES)
                image->setPixel({x, y}, sf::Color::Black);
            else
                image->setPixel({x, y}, sf::Color(15*n, 0, 255 - 10*n));
        }
    }
}


void DrawMandelbrot()
{
    MandelbrotInfo data = {};
    data.window_width   = WINDOW_WIDTH;
    data.window_height  = WINDOW_HEIGHT;

    data.x_shift    = DEFAULT_SHIFT_X;
    data.y_shift    = DEFAULT_SHIFT_Y;
    data.zoom       = DEFAULT_ZOOM;

    data.arr_iters  = (int*) calloc(WINDOW_WIDTH * WINDOW_HEIGHT, sizeof(int));

    sf::Vector2u        window_size (WINDOW_WIDTH, WINDOW_HEIGHT);
    sf::VideoMode       video_mode  (window_size, BITS_PER_PIXEL);
    sf::RenderWindow    window      (video_mode, WINDOW_NAME);

    sf::Image           image       (window_size, sf::Color::White);
    sf::Texture         texture     (window_size);
    sf::Sprite          sprite      (texture);

    while (window.isOpen())
    {
        CheckEvents(&window, &data);

        double fps = GetMandelbrotTime(&data, CalcMandelbrotWithColors);
        printf("%lf\n", fps);

        DrawDots(&image, data.arr_iters);

        int text_load_status = texture.loadFromImage(image);
        if (!text_load_status)
            continue;

        sprite.setTexture(texture, true);

        window.clear();
        window.draw(sprite);
        window.display();
    }

    free(data.arr_iters); data.arr_iters = NULL;
}


static double GetMandelbrotTime(MandelbrotInfo* data, void (*CalcMandelbrotFunc)(MandelbrotInfo* data))
{
    struct timeval start_time = {};
    gettimeofday(&start_time, NULL);

    CalcMandelbrotFunc(data);

    struct timeval end_time = {};
    gettimeofday(&end_time, NULL);

    return 1.0 / (((double) end_time.tv_sec - end_time.tv_sec) +
                  ((double) end_time.tv_usec - start_time.tv_usec) / MICROSEC_TO_SEC);
}


static void ZoomDown(MandelbrotInfo* data)
{
    data->x_shift = ZOOM_DOWN_SHIFT_COEF * data->zoom + data->x_shift;
    data->y_shift = ZOOM_DOWN_SHIFT_COEF * data->zoom + data->y_shift;
    data->zoom *= ZOOM_COEF;
}


static void ZoomUp(MandelbrotInfo* data)
{
    data->x_shift = ZOOM_UP_SHIFT_COEF * data->zoom + data->x_shift;
    data->y_shift = ZOOM_UP_SHIFT_COEF * data->zoom + data->y_shift;
    data->zoom /= ZOOM_COEF;
}
