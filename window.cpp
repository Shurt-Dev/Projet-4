#include "header.h"
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>



Window::Window() {
    this->renderer = NULL;
    this->window = NULL;
    this->screenSurface = NULL;
    this->texture = NULL;

    this->width = NULL;
    this->height = NULL;

    this->stretchRect;
    this->stretchRect.x = NULL;
    this->stretchRect.y = NULL;
    this->stretchRect.w = NULL;
    this->stretchRect.h = NULL;

    TTF_Font* font = NULL;
};



Window::~Window() {
    //Deallocate surface
    SDL_FreeSurface(screenSurface);
    screenSurface = NULL;

    //Free loaded image
    SDL_DestroyTexture(texture);
    texture = NULL;

    //Free global font
    TTF_CloseFont(font);
    font = NULL;

    //Destroy window    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
};



SDL_Window* Window::GetWindow() {
    return this->window;
};



SDL_Renderer* Window::GetRenderer() {
    return this->renderer;
};



SDL_Surface* Window::GetSurface()
{
    if (window == NULL){return NULL;}

    screenSurface = SDL_GetWindowSurface(window);
    return screenSurface;
};



int Window::Init(const char* name, int width, int height) {

    this->width = width;
    this->height = height;
    // Init SDL:
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Init the main SDL window:
    Uint32 window_flags = 0;
    this->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
    if (this->window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Init renderer within the main SDL window:
    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    this->renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (this->renderer == NULL) {
        printf("SDL2 error while creating renderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Fill renderer background:
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);
    SDL_RenderPresent(this->renderer);

    //Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    return EXIT_SUCCESS;
};



int Window::SurfaceUpdate()
{
    //Update the surface
    SDL_UpdateWindowSurface(this->window);
    return 0;
};



int Window::FillSurface(Uint32 color)
{
    SDL_FillRect(screenSurface, NULL, color);
    return 0;
};



int Window::LoadMediaBMP(int x, int y, int w, int h, std::string path)
{
    //Load splash image
    SDL_Surface* media = SDL_LoadBMP(path.c_str());
    if (media == NULL)
    {
        printf("Unable to load image at %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface* optimizedSurface = NULL;

    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(media, screenSurface->format, 0);
    if (optimizedSurface == NULL)
    {
        printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    SDL_FreeSurface(media);

    //Apply the image stretched
    SDL_Rect stretchRect;
    stretchRect.x = x;
    stretchRect.y = y;
    stretchRect.w = w;
    stretchRect.h = h;
    SDL_BlitScaled(optimizedSurface, NULL, screenSurface, &stretchRect);

    return 0;
};



int Window::LoadMediaPNG(int x, int y, int w, int h, std::string path)
{
    //Load PNG image
    SDL_Surface* media = IMG_Load(path.c_str());
    if (media == NULL)
    {
        printf("Unable to load image at %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return EXIT_FAILURE;
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(media);

    SDL_Surface* optimizedSurface = NULL;

    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface(media, screenSurface->format, 0);
    if (optimizedSurface == NULL)
    {
        printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    SDL_FreeSurface(media);

    //Apply the image stretched
    SDL_Rect stretchRect;

    this->stretchRect.x = x;
    this->stretchRect.y = y;
    this->stretchRect.w = w;
    this->stretchRect.h = h;
    SDL_BlitScaled(optimizedSurface, NULL, screenSurface, &stretchRect);

    return 0;
};



SDL_Texture* Window::LoadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    //Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);

    return newTexture;
};



int Window::DrawRect(int x, int y, int w, int h, int color, int option)
{
    SDL_Rect Rect{};
    Rect.x = x;
    Rect.y = y;
    Rect.w = w;
    Rect.h = h;

    int r = color >> 16 & 0xFF;
    int g = color >> 8 & 0xFF;
    int b = color & 0xFF;
    switch (option)
    {
    case 1:
        SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
        SDL_RenderDrawRect(renderer, &Rect);
    default:
        SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
        SDL_RenderFillRect(renderer, &Rect);
    }
    return 0;
};


int Window::TextureText(int x, int y, int w, int h, std::string path, int tSize, std::string text, int tColor, SDL_Renderer* rend)
{
    SDL_Texture* newTexture = NULL;

    //Open the font
    font = TTF_OpenFont(path.c_str(), 28);
    if (font == NULL)
    {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    //Render text
    Uint8 r = tColor >> 16 & 0xFF;
    Uint8 g = tColor >> 8 & 0xFF;
    Uint8 b = tColor & 0xFF;
    SDL_Color textColor = { r, g, b };

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n 1\n", TTF_GetError());
        return 1;
    }

    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (newTexture == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    //Get rid of old surface
    SDL_FreeSurface(textSurface);

    //Set rendering space and render to screen
    SDL_Rect renderQuad{};
    renderQuad.x = x;
    renderQuad.y = y;
    renderQuad.w = w;
    renderQuad.h = h;

    //Render to screen
    SDL_RenderCopy(renderer, newTexture, NULL, &renderQuad);

    return 0;
};


int Window::ViewPort(int x, int y, int w, int h, std::string path)
{
    //Current displayed texture
    SDL_Texture* texture = NULL;

    //Load texture
    texture = this->LoadTexture(path.c_str());
    if (texture == NULL)
    {
        printf("Failed to load texture image!\n");
    }

    //Top right viewport
    SDL_Rect Viewport{ 0 };
    Viewport.x = x;
    Viewport.y = y;
    Viewport.w = w;
    Viewport.h = h;
    SDL_RenderSetViewport(GetRenderer(), &Viewport);

    //Render texture to screen
    SDL_RenderCopy(GetRenderer(), texture, NULL, NULL);

    return 0;
};