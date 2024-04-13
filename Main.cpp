#include <iostream>

#include "Engine.hpp"

Engine engine;

int main(int argc, char* argv[]) {

    std::cout << "Bellaaaaa ci sono anch'io - versione 0.1 - it2000" << std::endl;

    srand(time(NULL));

    engine.init();

    while (engine.running()) {

        engine.update();
        engine.render();
        engine.handleEvents();
    }

    return 0;
}