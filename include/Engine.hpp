#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <iostream>

#include "Element.hpp"
#include "ECS.hpp"

enum Groups : std::size_t { // Definizione dei gruppi di rendering

    Gplayer,
    Gasteroids,
    Glasers,
    Gdebris,
    Gbackground
};

enum Categories : int16 { // Definizione dei gruppi di collisione

    Cplayer   = 0x0001,
    Claser    = 0x0002,
    Casteroid = 0x0004,
    Cdebris   = 0x0008
};

using Elements = std::map<std::string, Element*>;

const int FPS = 60;
const float frameDelay = 1.f / FPS;

const std::string title = "Explosion 0.1 - it2000";
const int WW = 800; // Window Width
const int WH = 500; // Window Height

const int32 velocityIterations = 6;
const int32 positionIterations = 2;
const float WS = 100.f; // World Scale

class Engine {

public:

    void init();
    void update();
    void render();
    void handleEvents();
    bool running();
    void clean();

    void loadElements();

    static sf::RenderWindow* window;
    static Elements elements;
    static Manager manager;
    static b2World* world;

private:

    sf::Event event;
};