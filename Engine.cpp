#include "Engine.hpp"
#include "Element.hpp"
#include "Asset.hpp"
#include "Components.hpp"

const std::vector<Asset> assets = {

    {"assets/textures/playerShip3_blue.png", "player", 98, 75, 0.5f},
    {"assets/textures/meteorBrown_big3.png", "meteor", 89, 82, 0.5f},
    {"assets/textures/laserBlue16.png",      "laser",  13, 54, 0.5f},
};

void Engine::init() {

    window.create(sf::VideoMode(windowWidth, windowHeight), "Explosion test", sf::Style::Close);
    window.setFramerateLimit(FPS);
    world = new b2World(gravity);
    loadElements();

    b2PolygonShape shape;
    shape.SetAsBox(0.245f, 0.1875f);

    b2CircleShape shape2;
    shape2.m_radius = 0.41f;

    auto entity = registry.create();
    auto asteroid = registry.create();

    auto playerBody = registry.emplace<Body>(entity, world, b2_dynamicBody, 4.3f, 1.f);

    registry.emplace<Sprite>(entity, elements["player"]);
    registry.emplace<Controller>(entity);
    registry.emplace<Teleporter>(entity);
    registry.emplace<Weapon>(entity, elements["laser"], playerBody.body, &registry);
    
    auto asteroidBody = registry.emplace<Body>(asteroid, world, b2_dynamicBody, 4.f, 2.5f);

    registry.emplace<Sprite>(asteroid, elements["meteor"]);
    registry.emplace<Teleporter>(asteroid);

    asteroidBody.setShape(shape2, 10.f);
    playerBody.setShape(shape, 1.f);
}

void Engine::update() {

    world->Step(frameDelay, velocityIterations, positionIterations);

    for (auto entity : registry.view<Body, Sprite, Teleporter>()) {

        auto& body = registry.get<Body>(entity);
        auto& sprite = registry.get<Sprite>(entity);
        auto& teleporter = registry.get<Teleporter>(entity);
        sprite.update(body.body);
        teleporter.update(body.body);
    }

    for (auto entity : registry.view<Body, Controller, Weapon>()) {

        auto& body = registry.get<Body>(entity);
        auto& controller = registry.get<Controller>(entity);
        auto& weapon = registry.get<Weapon>(entity);
        controller.checkInputs(body.body);
        weapon.checkInputs();
    }
}

void Engine::render() {

    window.clear();

    for (auto entity : registry.view<Sprite>()) {

        registry.get<Sprite>(entity).draw(&window);
    }

    window.display();
}

void Engine::handleEvents() {

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {

            window.close();
        }
    }
}

bool Engine::running() {

    return window.isOpen();
}

void Engine::loadElements() {

    for (auto asset : assets) {

        Element* element = new Element();

        if (!element->texture.loadFromFile(asset.path)) {
            window.close();
        }

        element->width = float(asset.width);
        element->height = float(asset.height);
        element->scale = asset.scale;
        elements.emplace(asset.name, element);
    }
}