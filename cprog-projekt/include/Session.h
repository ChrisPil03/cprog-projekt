#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
#include <SDL2/SDL.h>

namespace engine{

	class Session
	{
	public:
		Session();
		void addComponent(Component* c);
        void removeComponent(Component* c); // boolean?
        void setFps(const int newFps);
		const SDL_Keycode& getKeyDown() const;
		void run();
		~Session();
        
	private:
		std::vector<Component*> components;
        //vector with scenes instead of component?
        std::vector<Component*> added, removed;
        int fps = 60;
		const int tickInterval = 1000 / fps;
		SDL_Keycode keyDown;
        
	};

    extern Session session;
}
#endif