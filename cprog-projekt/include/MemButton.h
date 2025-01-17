#ifndef MEMBUTTON_H
#define MEMBUTTON_H

#include "Button.h"
#include <iostream>

namespace engine
{
    template <typename KLASS>
    class MemButton : public Button
    {
    public:
        static MemButton<KLASS>* getInstance(int x, int y, int w, int h, std::string imagePath, KLASS* object, void (KLASS::*function)()){
            return new MemButton(x,y,w,h,imagePath,object,function);
        }
        void execute(Button* source){ (object->*memberFunction)(); }
    protected:
        MemButton(int x, int y, int w, int h, std::string imagePath, KLASS* object, void (KLASS::*function)()) :
            Button(x,y,w,h,imagePath), object(object), memberFunction(function)
        {}
    private:
        KLASS* object;
        void (KLASS::*memberFunction)();
    };
}

#endif