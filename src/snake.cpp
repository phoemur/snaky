#include "snake.h"
#include "field.h"

#include <cmath>

Snake::Snake(Field* f, std::size_t init_size)
    : field{f}, size{init_size}, coordinates{}, next_dir{Directions::Right}
{
    // Get init position
    std::size_t y = field->get_height() / 2;
    std::size_t x = field->get_width() / 2;
    coordinates.emplace_back(y, x);
    (*field)[y][x] = Block::head;

    // Fill body of snake
    for (std::size_t i=1; i<size; ++i)
        if ((*field)[y][--x] == Block::empty) {
            coordinates.emplace_back(y, x);
            (*field)[y][x] = Block::body;
        }
        else {break;}
}

bool Snake::make_move()
{
    auto coord = coordinates.front();
    auto old = coord;

    switch(next_dir) {
        case Directions::Right:
            coord.second++;
            break;
        case Directions::Left:
            coord.second--;
            break;
        case Directions::Up:
            coord.first--;
            break;
        case Directions::Down:
            coord.first++;
            break;
    }

    if ((*field)[coord.first][coord.second] == Block::fruit) { // Hit a fruit
        increase_size();
        field->eat_fruit();
    }
    else if ((*field)[coord.first][coord.second] != Block::empty) { // Hit anything else
        return false;
    }

    // Update head
    (*field)[coord.first][coord.second] = Block::head;
    (*field)[old.first][old.second] = Block::body;
    coordinates.push_front(std::move(coord));

    // Erase the tail of the snake to fit size
    if (coordinates.size() > size) {
        auto last = coordinates.back();
        (*field)[last.first][last.second] = Block::empty;
        coordinates.pop_back();
    }

    return true;
}

void Snake::increase_size()
{
    ++size;
}

void Snake::set_direction(Directions dir)
{
    if (std::abs(static_cast<int>(dir) - static_cast<int>(next_dir)) >= 2) { // Avoid 180 degrees turns
        next_dir = dir;
    }
}

void Snake::handle_event(SDL_Event& e)
{
    if( e.type == SDL_KEYDOWN ) {
        switch( e.key.keysym.sym ) {
            case SDLK_UP:
            case SDLK_w:
                set_direction(Directions::Up);
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                set_direction(Directions::Right);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                set_direction(Directions::Left);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                set_direction(Directions::Down);
                break;
            default:
                break;
        }
    }
}
