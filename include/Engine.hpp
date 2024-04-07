#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <box2d/box2d.h>

#include <entt/entt.hpp>

#include <iostream>

// Questa è la classe perincipale, quella che gestisce tutto
// P.S. Scusate il mio linguaggio poco professionale
// (per linguaggio intendo il mio modo di esprimermi nei commenti)

struct Element;

const int FPS = 60;
const float frameDelay = 1.f / float(FPS);

const int windowWidth = 800;
const int windowHeight = 500;

const b2Vec2 gravity(0.f, 0.f);

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
const float WS = 100.f;

class Engine {

public:

    void init();
    void update();
    void render();
    void handleEvents();
    bool running();
    void clean();

    void loadElements();

    sf::RenderWindow window;
    b2World* world;

private:

    std::map<std::string, Element*> elements;
    entt::registry registry;
    sf::Event event;
};