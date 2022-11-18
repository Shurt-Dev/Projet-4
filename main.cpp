#include <iostream>
#include <string>
#include "header.h"
using namespace std;

string color;
int width, height;

int main(int argc, char* argv[]) {
	cout << "Enter width and height:" << endl;
	cin >> width;
	cin >> height;
	Window Test;
	Test.Init("SDL Window Test", width, height);
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while ((SDL_PollEvent(&e) != 0))
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			

			//Clear screen
			SDL_RenderClear(Test.GetRenderer());

			Test.TextureText(300, 200, 300, 200,
				"Roboto-Black.ttf", 32, 
				"Text here", 0xFFFFFF, Test.GetRenderer());

			//Update screen
			SDL_RenderPresent(Test.GetRenderer());
		}
	}
	return 0;
}