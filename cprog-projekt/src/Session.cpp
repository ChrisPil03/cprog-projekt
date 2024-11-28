#include "Constants.h"
#include "Session.h"
#include "Component.h"
#include "System.h"
#include <SDL2/SDL.h>

namespace engine{

void Session::addComponent(Component* c){
    added.push_back(c);
}

void Session::removeComponent(Component* c) {
	removed.push_back(c);
}

void Session::run() {
	bool quit = false;
}

}

