#include "Engine.hpp"
#include "Element.hpp"
#include "Assets.hpp"
#include "Components.hpp"
#include "Listener.hpp"

b2BodyDef playerBodyDef;
b2BodyDef asteroidBodyDef;
b2FixtureDef playerFixtureDef;
b2FixtureDef asteroidFixtureDef;

b2PolygonShape loadShape(std::vector<sf::Vector2i> _shape, float w, float h, float s);
void _setDefaultPlayerSettings();
void _setDefaultAsteroidSettings();
void _loadPlayer();
void _loadAsteroid();

std::map<std::string, Element*> Engine::elements;
sf::RenderWindow* Engine::window;
Manager Engine::manager;
b2World* Engine::world;
Listener listener;

auto& playerGroup    = Engine::manager.getGroup(Gplayer);
auto& asteroidsGroup = Engine::manager.getGroup(Gasteroids);
auto& lasersGroup    = Engine::manager.getGroup(Gasteroids);
auto& debrisGroup    = Engine::manager.getGroup(Gdebris);

void Engine::init() {

    window = new sf::RenderWindow(sf::VideoMode(WW, WH), title, sf::Style::Close);
    window->setFramerateLimit(FPS);
    world = new b2World(b2Vec2(0.f, 0.f));
    world->SetContactListener(&listener);
    loadElements();

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

    for (auto& e : debrisGroup)    e -> draw();
    for (auto& e : lasersGroup)    e -> draw();
    for (auto& e : asteroidsGroup) e -> draw();
    for (auto& e : playerGroup)    e -> draw();

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

b2PolygonShape loadShape(std::vector<sf::Vector2i> _shape, float w, float h, float s) {

    b2PolygonShape shape;

    if (!_shape.empty()) {

        b2Vec2 verts[_shape.size()];

        for (int i = 0; i < _shape.size(); i++) {

            b2Vec2 p(
                (float(_shape[i].x) - w / 2.f) * s / WS,
                -(float(_shape[i].y) - h / 2.f) * s / WS
            );

            verts[i].x = p.x; verts[i].y = p.y;
        }

        shape.Set(verts, _shape.size());
    }

    else shape.SetAsBox(w * s / WS / 2.f, h * s / WS / 2.f);

    return shape;
}

void _setDefaultPlayerSettings() {

    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(4.f, 2.5f);
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.filter.categoryBits = Cplayer;
    playerFixtureDef.filter.maskBits = Casteroid;
    playerFixtureDef.shape = &Engine::elements["player"]->shape;
}

void _setDefaultAsteroidSettings() {

    asteroidBodyDef.type = b2_dynamicBody;
    asteroidFixtureDef.density = 10.0f;
    asteroidFixtureDef.filter.categoryBits = Casteroid;
    asteroidFixtureDef.filter.maskBits = Claser | Cplayer;
    asteroidFixtureDef.shape = &Engine::elements["meteor"]->shape;
}

void _loadPlayer() {

    auto& spaceship = Engine::manager.addEntity();
    spaceship.addComponent<Body>(playerBodyDef, playerFixtureDef);
    spaceship.addComponent<Sprite>(Engine::elements["player"]);
    spaceship.addComponent<Controller>();
    spaceship.addComponent<Teleporter>();
    spaceship.addComponent<Weapon>(Engine::elements["laser"]);
    Engine::manager.addToGrop(&spaceship, Gplayer);
}

void _loadAsteroid() {

    auto& asteroid = Engine::manager.addEntity();
    asteroid.addComponent<Body>(asteroidBodyDef, asteroidFixtureDef);
    asteroid.addComponent<Sprite>(Engine::elements["meteor"]);
    asteroid.addComponent<Teleporter>();
    asteroid.getComponent<Body>().body->SetTransform(b2Vec2((rand() % (WW + 1)) / WS, (rand() % (WH + 1)) / WS), 0);

    std::vector<Element*> debris = {Engine::elements["meteor2"]};

    asteroid.addComponent<Asteroid>(20);
    Engine::manager.addToGrop(&asteroid, Gasteroids);
}