#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "font.h"

#include <string>
#include <SDL.h>

class MainWindow final {
    int width;
    int height;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
public:
    MainWindow(int w, int h, const std::string& title);
    ~MainWindow() noexcept;

    void set_icon(const std::string& path);
    void clear();
    void update();

    SDL_Renderer* get_renderer() const noexcept {return gRenderer;}
    SDL_Window*     get_window() const noexcept {return gWindow;  }
    int              get_width() const noexcept {return width;    }
    int             get_height() const noexcept {return height;   }
};

#endif // MAINWINDOW_H
