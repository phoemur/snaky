#include "field.h"

#include <algorithm>
#include <cassert>
#include <cmath>

Field::Field(int x_size, int y_size, MainWindow& m)
    : x{x_size}, y{y_size}, padding_x{0}, padding_y{0}, field{}, seeder{}, engine{seeder()}
{
    // Init brick texture
    block = std::make_unique<Texture>(m);
    block->loadFromFile("./snaky_assets/brick.png");

    // Init floor texture
    floor = std::make_unique<Texture>(m);
    floor->loadFromFile("./snaky_assets/floor.png");

    // Init body texture
    body = std::make_unique<Texture>(m);
    body->loadFromFile("./snaky_assets/body.png");

    // Init head texture
    head = std::make_unique<Texture>(m);
    head->loadFromFile("./snaky_assets/head.png");

    // Init apple texture
    apple = std::make_unique<Texture>(m);
    apple->loadFromFile("./snaky_assets/apple.png");

    // Init sound effect
    sound = std::make_unique<Sound>("./snaky_assets/scratch.wav");

    // Fix sizes
    assert(block->get_width()  == floor->get_width());
    assert(block->get_height() == floor->get_height());
    padding_x = block->get_width();
    padding_y = block->get_height();
    x /= padding_x;
    y /= padding_y;

    // Random generators
    dist_x = std::uniform_int_distribution<int>(0, x-1);
    dist_y = std::uniform_int_distribution<int>(0, y-1);

    // Init
    init_field();
}

void Field::render(int w, int h, Snake* ptr)
{
    for (int i=0; i<y; ++i) {
        for (int j=0; j<x; ++j) {
            switch(field[i][j]) {
                case Block::brick:
                    block->render(w+(padding_x * j), h+(padding_y * i));
                    break;
                case Block::empty:
                    floor->render(w+(padding_x * j), h+(padding_y * i));
                    break;
                case Block::body:
                    body->render(w+(padding_x * j), h+(padding_y * i));
                    break;
                case Block::head:
                    {
                    // Flip head acording to heading direction
                    SDL_RendererFlip flipType = SDL_FLIP_NONE;
                    double degrees = 0.0;

                    if (ptr != nullptr) {

                        switch(ptr->get_direction()) {
                            case Directions::Right:
                                break;
                            case Directions::Left:
                                flipType = SDL_FLIP_HORIZONTAL;
                                break;
                            case Directions::Up:
                                degrees = 90.0;
                                flipType = SDL_FLIP_HORIZONTAL;
                                break;
                            case Directions::Down:
                                degrees = 90.0;
                                break;
                        }
                    }

                    head->render(w+(padding_x * j), h+(padding_y * i), nullptr, degrees, nullptr, flipType);
                    break;
                    }
                case Block::fruit:
                    floor->render(w+(padding_x * j), h+(padding_y * i)); // Background
                    apple->render(w+(padding_x * j), h+(padding_y * i));
                    break;
                default:
                    break;
            }
        }
    }
}

void Field::add_random_obstacle(const std::pair<int, int>& snakehead)
{
    int i=0, j=0;

    while (field[i][j] != Block::empty) {
        i = dist_y(engine);
        j = dist_x(engine);

        // Ensure new obstacle is at least 5 far from snake's head
        if (std::hypot(i - snakehead.first, j - snakehead.second) < 5) {
            j = 0;
            i = 0;
        }
    }

    field[i][j] = Block::brick;
}

void Field::add_random_fruit()
{
    int i=0, j=0;

    while (field[i][j] != Block::empty) {
        i = dist_y(engine);
        j = dist_x(engine);
    }

    field[i][j] = Block::fruit;
}

void Field::eat_fruit()
{
    // Sound effect
    sound->play();

    // Add new fruit when eaten
    add_random_fruit();
}

void Field::init_field()
{
    field = std::vector<std::vector<Block>> (y, std::vector<Block>(x, Block::empty));

    std::fill(field[0].begin(), field[0].end(), Block::brick);
    std::fill(field.back().begin(), field.back().end(), Block::brick);

    for (auto& row: field) {
        row.back() = Block::brick;
        row.front() = Block::brick;
    }
}
