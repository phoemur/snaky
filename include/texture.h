#ifndef TEXTURE_H
#define TEXTURE_H

#include "mainwindow.h"
#include "font.h"

#include <SDL.h>
#include <string>

//Texture wrapper class
class Texture {
public:
    //Initializes variables
    Texture(MainWindow& m);

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile( const std::string& path );

    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, Font& f, SDL_Color textColor );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );

    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int  get_width() const noexcept {return mWidth; }
    int get_height() const noexcept {return mHeight;}

private:
    SDL_Texture* mTexture;
    SDL_Renderer* gRenderer;

    int mWidth;
    int mHeight;
};

#endif // TEXTURE_H
