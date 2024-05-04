#include "Engine.hpp"
#include "Assets.hpp"
#include "Random.hpp"
#include "Components.hpp"
#include "MonoBehaviour.hpp"
#include "Listener.hpp"
#include "Background.hpp"
#include "ExplosionsLoader.hpp"

b2BodyDef playerBodyDef;
b2BodyDef asteroidBodyDef;
b2FixtureDef playerFixtureDef;
b2FixtureDef asteroidFixtureDef;

auto loadShape(std::vector<sf::Vector2i>, float, float, float) -> b2PolygonShape;
void _setDefaultPlayerSettings();
void _setDefaultAsteroidSettings();
void _loadPlayer();
void _loadAsteroid();

sf::RenderWindow* Engine::window;
Elements Engine::elements;
Manager Engine::manager;
b2World* Engine::world;
Listener listener;

auto& playerGroup     = Engine::manager.getGroup(Gplayer);
auto& asteroidsGroup  = Engine::manager.getGroup(Gasteroids);
auto& lasersGroup     = Engine::manager.getGroup(Glasers);
auto& debrisGroup     = Engine::manager.getGroup(Gdebris);
auto& backgroundGroup = Engine::manager.getGroup(Gbackground);

void Engine::init() {

    window = new sf::RenderWindow(sf::VideoMode(WW, WH), title, sf::Style::Close);
    window->setFramerateLimit(FPS);
    world = new b2World(b2Vec2(0.f, 0.f));
    world->SetContactListener(&listener);
    loadElements();

	ExplosionsLoader::init();
    Background background("background");
    background.drawBackground();

    _setDefaultPlayerSettings();
    _setDefaultAsteroidSettings();
    _loadPlayer();
    _loadAsteroid();
}

void Engine::update() {

    manager.update();
    manager.refersh();

    world->Step(frameDelay, velocityIterations, positionIterations);
}

void Engine::render() {

    window->clear();

    for (auto& e : backgroundGroup) e -> draw();
    for (auto& e : debrisGroup)     e -> draw();
    for (auto& e : lasersGroup)     e -> draw();
    for (auto& e : asteroidsGroup)  e -> draw();
    for (auto& e : playerGroup)     e -> draw();

    window->display();
}

void Engine::handleEvents() {

    while (window->pollEvent(event)) {

        if (event.type == sf::Event::Closed) {

            window->close();
        }

        else if (event.type == sf::Event::KeyPressed) {

            if (event.key.scancode == sf::Keyboard::Scan::M) {

                _loadAsteroid();
            }
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
        element->shape = loadShape(asset.shape, float(asset.width), float(asset.height), element->scale);
        elements.emplace(asset.name, element);
    }
}

Engine::~Engine() {

	delete window;
	delete world;
}

b2PolygonShape loadShape(std::vector<sf::Vector2i> sh, float w, float h, float s) {

    b2PolygonShape shape;

    if (!sh.empty()) {

        b2Vec2 verts[sh.size()];

        for (int i = 0; i < sh.size(); i++) {

            b2Vec2 p(
                +(float(sh[i].x) - w / 2.f) * s / WS,
                -(float(sh[i].y) - h / 2.f) * s / WS
            );

            verts[i].x = p.x; verts[i].y = p.y;

        } shape.Set(verts, sh.size());
    }

    else shape.SetAsBox(w * s / WS / 2.f, h * s / WS / 2.f);

    return shape;
}

void _setDefaultPlayerSettings() {

    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(4.f, 2.5f);
    playerBodyDef.linearDamping = 1.f;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.filter.categoryBits = Cplayer;
    playerFixtureDef.filter.maskBits = Casteroid;
    playerFixtureDef.shape = &Engine::elements["player"]->shape;
}

void _setDefaultAsteroidSettings() {

    asteroidBodyDef.type = b2_dynamicBody;
    asteroidBodyDef.linearDamping = 1.f;
    asteroidFixtureDef.density = 10.0f;
    asteroidFixtureDef.filter.categoryBits = Casteroid;
    asteroidFixtureDef.filter.maskBits = Claser | Cplayer;
    asteroidFixtureDef.shape = &Engine::elements["meteor"]->shape;
}

void _loadPlayer() {

    auto& spaceship = Engine::manager.addEntity();
    spaceship.addComponent<Body>(playerBodyDef, playerFixtureDef);
    spaceship.addComponent<Teleporter>();
    spaceship.addComponent<Sprite>("player");
    spaceship.addComponent<Weapon>("laser");
    spaceship.addMonoBehaviour<Spaceship>();
    Engine::manager.addToGrop(&spaceship, Gplayer);
}

void _loadAsteroid() {

    auto& asteroid = Engine::manager.addEntity();

    b2Vec2 pos = b2Vec2(
        (rand() % (WW + 1)) / WS, 
        (rand() % (WH + 1)) / WS
    );

    asteroid.addComponent<Body>(asteroidBodyDef, asteroidFixtureDef);
    asteroid.addComponent<Sprite>("meteor");
    asteroid.addComponent<Teleporter>();
    asteroid.getComponent<Body>().setPosition(pos);
    asteroid.addMonoBehaviour<Asteroid>();
    Engine::manager.addToGrop(&asteroid, Gasteroids);
}