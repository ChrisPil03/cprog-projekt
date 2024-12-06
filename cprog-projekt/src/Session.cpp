#include "Constants.h"
#include "Session.h"
#include "Component.h"
#include "System.h"
#include <SDL2/SDL.h>

namespace engine{

    Session::Session(){}

    void Session::addComponent(Component* c){
        added.push_back(c);
    }

    void Session::removeComponent(Component* c) {
        removed.push_back(c);
    }

    const bool Session::keyDown(const SDL_Keycode& key) const{
        return keysDown.find(key) != keysDown.end();
    }

// main loop, checks for events and updates components
    void Session::run() {
        bool quit = false;
        while(!quit){
            Uint32 nextTick = SDL_GetTicks() + tickInterval;
            SDL_Event event;
            while (SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT: quit = true; break;
                    case SDL_KEYDOWN:
                        keysDown.insert(event.key.keysym.sym);
                        break;
                    case SDL_KEYUP:
                        keysDown.erase(event.key.keysym.sym);
                } // yttre switch
            } // inre while

            for (Component* c : components){
                c->update();
            }

            for (Component* c : added){
                components.push_back(c);
            }
            added.clear();
            
            for (Component* c : removed){
                for (std::vector<Component*>::iterator iter = components.begin(); iter != components.end();){
                    if (*iter == c){
                        delete *iter;
                        iter = components.erase(iter);
                    }
                    else{
                        iter++;
                    }
                }
            }
            removed.clear();

            

            SDL_RenderClear(system.getRen());
            for (Component* c : components){
                c->render();
            }
            SDL_RenderPresent(system.getRen());

            int delay = nextTick - SDL_GetTicks();
            if (delay > 0){
                SDL_Delay(delay);
            }

        } // yttre while
    } // run

    void Session::setFps(int newFps){
        fps= newFps;
    }

    const std::vector<Component*>& Session::getComponents() const { return components;}

    Session::~Session(){

    }

    Session session;
}

