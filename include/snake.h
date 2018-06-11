#ifndef SNAKE_H
#define SNAKE_H

#include <SDL.h>
#include <deque>
#include <utility>

// Forward declaration
class Field;

enum class Directions {
    Up=1, Down=2, Left=5, Right=6
};

class Snake {
    Field* field;
    std::size_t size;
    std::deque<std::pair<int, int>> coordinates; // Store all pieces of the snake's body

    Directions next_dir;
public:
    Snake(Field* f, std::size_t init_size);

    bool make_move();
    void increase_size();
    void set_direction(Directions dir);
    void handle_event(SDL_Event& e);
    std::pair<int,int> get_coordinate() const {return coordinates.front();}
    Directions get_direction() const noexcept {return next_dir;}
    std::size_t score() const {return size;}
};

#endif // SNAKE_H
