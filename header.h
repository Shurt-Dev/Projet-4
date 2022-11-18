#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Window
{
protected:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Texture* texture;
	int width, height;
	TTF_Font* font;

public:
	SDL_Rect stretchRect;

	Window();
	~Window();
	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
	SDL_Surface* GetSurface();

	int Init(const char* winname, int width_, int height_); //init SDL lib and window
	int SurfaceUpdate(); //update the window (to use with surface fonctions)

	int FillSurface(Uint32 color); //expect hexadecimal format
	int LoadMediaBMP(int x, int y, int w, int h, std::string path); //load bitmap img on buffer with surface
	int LoadMediaPNG(int x, int y, int w, int h, std::string path); //load PNG img on buffer with surface
	SDL_Texture* LoadTexture(std::string path); //load PNG img with renderer
	int DrawRect(int x, int y, int w, int h, int color = 0x000000, int option = 0); //draw filled rectangle(option=0) or outlined rectangle (option=1)
	int TextureText(int x, int y, int w, int h, std::string path, int tSize, std::string text, int tColor, SDL_Renderer* rend);
	int ViewPort(int x, int y, int w, int h, std::string path);
};

