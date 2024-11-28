#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace engine 
{

	class System
	{
	public:
		System();
		~System();
		SDL_Renderer* getRen() const;
		TTF_Font* getFont() const;
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
        
	};
	
	extern System system;
}
#endif