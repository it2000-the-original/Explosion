#include "Engine.hpp"
#include "Element.hpp"
#include "Asset.hpp"
#include "Components.hpp"

sf::RenderWindow* Engine::window;
Manager Engine::manager;
b2World* Engine::world;

const std::vector<Asset> assets = {

    {"assets/textures/playerShip3_blue.png", "player", 98, 75, 0.5f},
    {"assets/textures/meteorBrown_big3.png", "meteor", 89, 82, 0.5f},
    {"assets/textures/laserBlue16.png",      "laser",  13, 54, 0.5f},
};

void Engine::init() {

    window = new sf::RenderWindow(sf::VideoMode(WW, WH), title, sf::Style::Close);
    window->setFramerateLimit(FPS);
    world = new b2World(b2Vec2(0.f, 0.f));
    loadElements();

    b2BodyDef definition;
    definition.type = b2_dynamicBody;
    definition.position.Set(4.f, 2.5f);

    b2PolygonShape shape;
    shape.SetAsBox(0.49f, 0.375f);

    b2FixtureDef fixture;
    fixture.shape = &shape;
    fixture.density = 1.0f;

    auto& spaceship = manager.addEntity();
    spaceship.addComponent<Body>(definition, fixture);
    spaceship.addComponent<Sprite>(elements["player"]);
    spaceship.addComponent<Controller>();
    spaceship.addComponent<Teleporter>();
}

void Engine::update() {

    world->Step(frameDelay, velocityIterations, positionIterations);

    manager.update();
    manager.refersh();
}

void Engine::render() {

    window->clear();
    manager.draw();
    window->display();
}

void Engine::handleEvents() {

    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {

            window->close();
        }
    }
}

bool Engine::running() {

    return window->isOpen();
}

void Engine::loadElements() {

    for (auto asset : assets) {

        Element* element = new Element();

        if (!element->texture.loadFromFile(asset.path)) {
            window->close();
        }

        element->width = float(asset.width);
        element->height = float(asset.height);
        element->scale = asset.scale;
        elements.emplace(asset.name, element);
    }
}