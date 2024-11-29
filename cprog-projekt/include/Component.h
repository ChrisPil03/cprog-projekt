#ifndef COMPONENT_H
#define COMPONENT_H

namespace engine{
    class Component
    {
    public:
        virtual ~Component(){}
        virtual void render() const {}
        virtual void update(){}
        virtual void moveRight(){}
        virtual void moveLeft(){}
        virtual void moveUp(){}
        virtual void moveDown(){}

    protected:
        Component(){}

    private:
        Component(const Component&) = delete;            
        const Component* operator=(const Component&) = delete;


    };
        
}

#endif