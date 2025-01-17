#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
#include <SDL2/SDL.h>
#include <set>
#include <string>

namespace engine{
	class Session
	{
	public:
		Session();
		void addComponent(Component* c);
        void removeComponent(Component* c);
        void setFps(const int newFps);
		const bool keyDown(std::string key) const;
		const std::vector<Component*>& getComponents() const;
		void run();
		~Session(){}
	private:
		void updateComponents();
		void renderComponents();
		void addComponents();
		void removeComponents();

		std::vector<Component*> components;
        std::vector<Component*> added, removed, childrenRemoved;
        int fps = 60;
		const int tickInterval = 1000 / fps;
		std::set<std::string> keysDown;
		bool removingComponents = false;
	};

    extern Session session;
}
#endif