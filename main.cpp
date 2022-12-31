#include "definitions.h"

int main() {
   
    Application vulkanApp;

    try {
        vulkanApp.run();
    }
    catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        return 1; // return failure
    }
    return 0;
}