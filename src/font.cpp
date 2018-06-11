#include "font.h"
#include "exception.h"

#include <algorithm>

Font::Font()
    : gFont{nullptr} {}

Font::Font(const std::string& path, int size)
    : Font()
{
    gFont = TTF_OpenFont( path.c_str(), size );
    if (gFont == nullptr) {
        throw SnakeException(std::string("Failed to load font! SDL_ttf Error: ") + TTF_GetError());
    }
}


Font::~Font() noexcept
{
    if (gFont != nullptr) {
        TTF_CloseFont( gFont );
    }
}
