#include <iostream>
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Renderer/Renderer.hpp"
#include "Kotoba/Window/Window.hpp"

int main(){
        
    Kotoba::Window window{{}};

    Kotoba::Renderer renderer{window};
    

    try{
        
        while(!window.shouldClose()){
            
            renderer.queue(Kotoba::Renderer::Line{{0,0}, {1000,1000},{255, 255, 255, 255}});

            renderer.beginFrame();
            renderer.draw();
            renderer.endFrame();
        }

    }catch(Kotoba::Exception& e){

        std::cout << e.what();
    }

    return 0;
}