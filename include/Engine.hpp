#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <box2d/box2d.h>

#include <iostream>

enum groups : std::size_t {

	bullets,
	asteroids,
	player,
};

enum Categories : int16 {

    Cplayer   = 0x0001,
    Claser    = 0x0002,
    Casteroid = 0x0004,
    Cdebris   = 0x0008
};

struct Element;
class Manager;

const int FPS = 60;
const float frameDelay = 1.f / float(FPS);

const std::string title = "Explosion Test";
const int WW = 800; // Window Width
const int WH = 500; // Window Height

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

    static std::map<std::string, Element*> elements;
    static sf::RenderWindow* window;
    static Manager manager;
    static b2World* world;

private:

    sf::Event event;
};