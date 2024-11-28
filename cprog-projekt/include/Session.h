#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
namespace engine{


	class Session
	{
	public:
		Session();
		void addComponent(Component* c);
        void removeComponent(Component* c); // boolean?
        void setFps(const int newFps);
		void run();
		~Session();
	private:
		std::vector<Component*> comps;
        //vector with scenes instead of component?
        std::vector<Component*> added, removed;
        int fps = 60;
	};

    extern Session ses;
}
#endif