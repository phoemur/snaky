#ifndef FIELD_H
#define FIELD_H

#include "texture.h"
#include "mainwindow.h"
#include "snake.h"
#include "music.h"

#include <vector>
#include <random>
#include <memory>

enum class Block : char {
    empty=0,
    brick,
    body,
    head,
    fruit
};

class Field {
    int x, y, padding_x, padding_y;
    std::vector<std::vector<Block>> field;

    std::random_device seeder;
    std::mt19937 engine;
    std::uniform_int_distribution<int> dist_x, dist_y;

    std::unique_ptr<Texture> block {nullptr};
    std::unique_ptr<Texture> floor {nullptr};
    std::unique_ptr<Texture> body  {nullptr};
    std::unique_ptr<Texture> head  {nullptr};
    std::unique_ptr<Texture> apple {nullptr};

    std::unique_ptr<Sound> sound {nullptr};
public:
    Field(int x_size, int y_size, MainWindow& m);

    void render(int w=0, int h=0, Snake* ptr = nullptr);
    void add_random_obstacle(const std::pair<int,int>& snakehead);
    void add_random_fruit();
    void eat_fruit();

    std::vector<Block>&       operator[](std::size_t y)       noexcept {return field[y];}
    const std::vector<Block>& operator[](std::size_t y) const noexcept {return field[y];}
    int get_width()  const noexcept {return x;}
    int get_height() const noexcept {return y;}
private:
    void init_field();
};

#endif // FIELD_H
