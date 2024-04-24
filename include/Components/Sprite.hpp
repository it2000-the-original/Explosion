// Gestisce un sf::Sprite per la rappresentazione grafica di Body

class Sprite : public Component {

private:

    Body* body;

    bool show = true;

public:

    float width;
    float height;
    float scale;

    sf::Sprite sprite;

    Sprite(Element* element) {

        scale =  element->scale;
        width =  element->width  * element->scale;
        height = element->height * element->scale;
        
        sprite.setTexture(element->texture);
        sprite.setScale(sf::Vector2f(scale, scale));
        sprite.setOrigin(sf::Vector2f(width / scale / 2.f, height / scale / 2.f));
        sprite.setTextureRect(sf::IntRect(0, 0, width / scale, height / scale));
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

        if (show) Engine::window->draw(sprite);
    }

    void hide(bool val) {

        show = !val;
    }
};