// Progetto per per la sfida di programmazione di PizzaGameDev
// P.S. Scusate per il mio linguaggio poco professionale
// Autore: it2000

#include <iostream>
#include <random>

#include "Engine.hpp"

Engine engine;

int main(int argc, char* argv[]) {

    std::cout << "Explosion - versione 0.1 - it2000" << std::endl;
    std::cout << "Per spawnare un asteroide, premere il tasto \"M\"";

    srand(time(NULL));

    engine.init();

    while (engine.running()) {

        engine.update();
        engine.render();
        engine.handleEvents();
    }

    return 0;
}