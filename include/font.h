#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>

// SDL_ttf true type font wrapper
class Font
{
    TTF_Font* gFont;

public:
    Font();
    Font(const std::string& path, int size);
    ~Font() noexcept;

    Font(const Font&) = delete;
    Font& operator=(const Font&) = delete;
    Font(Font&&) noexcept = default;
    Font& operator=(Font&&) = default;

    TTF_Font* get_font() const noexcept {return gFont;}
};

#endif // FONT_H
