#include <iostream>
#include "Kotoba/Core/Exception.hpp"
#include "Kotoba/Window/Window.hpp"

int main(){
    
    try{
        
        Kotoba::Window window{{}};

    }catch(Kotoba::Exception& e){

        std::cout << e.what();
    }

    return 0;
}