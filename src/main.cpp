#include "mainwindow.h"
#include "font.h"
#include "texture.h"
#include "field.h"
#include "snake.h"
#include "music.h"

#include <SDL.h>

#include <iostream>
#include <chrono>
#include <string>

constexpr static int WIDTH  = 640;
constexpr static int HEIGHT = 480;

int main()
{
    using namespace std::chrono;

    // Create Mainwindow
    MainWindow win(WIDTH, HEIGHT, "Snaky");
    win.set_icon("./snaky_assets/apple.png");

    // Create Title
    Font font ("./snaky_assets/lazy.ttf", 18);
    Texture title (win);
    title.loadFromRenderedText("Eat as many fruits as possible.", font, SDL_Color{0xFF,0,0,0xFF});

    // Create Field of play
    auto avail_height = win.get_height() - (title.get_height()*2);
    Field field(WIDTH, avail_height, win);

    // Create Snake on the field
    Snake snake(&field, 6);

    // Add 2 fruits
    field.add_random_fruit();
    field.add_random_fruit();

    // Background Music
    Music music ("./snaky_assets/chpn_op66.mp3");
    music.play();

    // Game Loop
    auto t1 = steady_clock::now();
    SDL_Event e;
    auto score1 = snake.score();
    bool quit = false;
    while (!quit) {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ) {
            //User requests quit
            if( e.type == SDL_QUIT ) {
                quit = true;
            }
            //User presses a key
            snake.handle_event(e);
        }

        // Add an obstacle every 10 seconds
        auto s2 = steady_clock::now();
        auto duration2 = duration_cast<seconds>( s2 - t1 ).count();
        if (duration2 > 10) {
            field.add_random_obstacle(snake.get_coordinate());
            t1 = s2;
        }

        // Update Title if score changed
        auto score2 = snake.score();
        if (score2 > score1) {
            title.loadFromRenderedText("Eat as many fruits as possible. Score: " + std::to_string(snake.score()), font, SDL_Color{0xFF,0,0,0xFF});
            score1 = score2;
        }


        // Try moving
        if(!snake.make_move()) { // Loose
            Texture t (win);
            t.loadFromRenderedText("YOU LOOSE!!! Score: " + std::to_string(snake.score()), font, SDL_Color{0xFF,0,0,0xFF});
            win.clear();
            t.render(( win.get_width() - t.get_width() ) / 2, ( win.get_height() - t.get_height() ) / 2 );
            win.update();

            SDL_Delay(5000);
            break;
        }


        // Render
        win.clear();

        title.render( ( win.get_width() - title.get_width() ) / 2, ( title.get_height() ) / 2 );
        field.render(0, title.get_height()*2, &snake);

        win.update();

        // Wait 100ms
        SDL_Delay(100);
    }

    return 0;
}
