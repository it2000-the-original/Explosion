// Questo componente ha la funzione di fare da effetto
// pacman, quando ci si trova al bordo dello schermo,
// si viene trasportati dall'altro lato

class Teleporter : public Component {

private:

    Body* body;
    Sprite* sprite;

    bool drawMirror = true;

public:

    // È uno sprite che rappresente la sporgenza
    // dell'originale, dall'altro lato dello schermo

    sf::Sprite mirror;

    bool teleporting = false;

    Teleporter() {}

    Teleporter(bool _drawMirror) {

        drawMirror = _drawMirror;
    }

    void init() {

        body = &entity->getComponent<Body>();
        sprite = &entity->getComponent<Sprite>();

        mirror.setTexture(*sprite->sprite.getTexture());
        mirror.setScale(sprite->sprite.getScale());
        mirror.setOrigin(sprite->sprite.getOrigin());
    }

    void update() {

        teleport();
        setMirror();
    }

    void draw() {

        if (teleporting and drawMirror) {

            Engine::window->draw(mirror);
        }
    }

    void teleport() {

        b2Vec2 pos = body->body->GetPosition();

        if      (pos.x > WW / WS) pos.x = 0.f;
        else if (pos.x <   0.f  ) pos.x = WW / WS;
        if      (pos.y > WH / WS) pos.y = 0.f;
        else if (pos.y <   0.f  ) pos.y = WH / WS;

        body->body->SetTransform(pos, body->body->GetAngle());
    }

    void setMirror() {

        sf::Vector2f pos = sprite->sprite.getPosition();
        float hproj = getHorizontalProjection();
        float vproj = getVerticalProjection();

        if (_rightMirror(hproj, &pos) or _leftMirror(hproj, &pos) or
            _downMirror(vproj, &pos) or _upMirror(vproj, &pos)) {

            teleporting = true;
        }

        else teleporting = false;

        mirror.setColor(sprite->sprite.getColor());
        mirror.setRotation(sprite->sprite.getRotation());
        mirror.setPosition(pos);
    }

    float getHorizontalProjection() {

        float side1 = fabs(sprite->width  * cos(body->body->GetAngle()));
        float side2 = fabs(sprite->height * sin(body->body->GetAngle()));
        return (side1 + side2) / 2.f;
    }

    float getVerticalProjection() {

        float side1 = fabs(sprite->width  * sin(body->body->GetAngle()));
        float side2 = fabs(sprite->height * cos(body->body->GetAngle()));
        return (side1 + side2) / 2.f;
    }

    bool _rightMirror(float proj, sf::Vector2f* pos) {

        if (pos->x + proj >= WW) {
            pos->x = pos->x - WW;
            return true;
        }

        return false;
    }

    bool _leftMirror(float proj, sf::Vector2f* pos) {

        if (pos->x - proj < 0.f) {
            pos->x = pos->x + WW;
            return true;
        }

        return false;
    }

    bool _downMirror(float proj, sf::Vector2f* pos) {

        if (pos->y + proj >= WH) {
            pos->y = pos->y - WH;
            return true;
        }

        return false;
    }

    bool _upMirror(float proj, sf::Vector2f* pos) {

        if (pos->y - proj < 0.f) {
            pos->y = pos->y + WH;
            return true;
        }

        return false;
    }
};