// Rappresentazione grafica del componente Body

class Sprite : public Component {

private:

    Body* body;

public:

    float width;
    float height;
    sf::Sprite sprite;

    Sprite(Element* element) {

        sprite.setTexture(element->texture);
        sprite.setScale(sf::Vector2f(element->scale, element->scale));
        sprite.setOrigin(sf::Vector2f(element->width / 2.f, element->height / 2.f));

        width = element->width * element->scale;
        height = element->height * element->scale;
    }

    void init() {

        body = &entity->getComponent<Body>();
    }

    void update() {

        b2Vec2 pos = body->body->GetPosition();
        float ang = body->body->GetAngle();

        sprite.setPosition(sf::Vector2f(pos.x * WS, pos.y * WS));
        sprite.setRotation(ang * 180.f / M_PI);
    }

    void draw() {

        Engine::window->draw(sprite);
    }
};