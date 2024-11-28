#ifndef COMPONENT_H
#define COMPONENT_H

namespace engine{
    class Component
    {
    public:
        virtual ~Component();
        virtual void render() const {}
        virtual void update(){}

    protected:
        Component(){}

    private:
        Component(const Component&) = delete;            
        const Component* operator=(const Component&) = delete;


    };
        
}

#endif