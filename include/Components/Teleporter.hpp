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

    sf::Sprite xMirror; // Specchio per la proiezione orizzontale
    sf::Sprite yMirror; // Specchio per la proiezione verticale

    bool xTeleporting = false;
    bool yTeleporting = false;

    Teleporter() {}

    Teleporter(bool _drawMirror) {

        drawMirror = _drawMirror;
    }

    void init() {

        body = &entity->getComponent<Body>();
        sprite = &entity->getComponent<Sprite>();
    }

    void update() {

        teleport();
        setXMirror();
        setYMirror();
    }

    void draw() {

        if (drawMirror) {

            if (xTeleporting) Engine::window->draw(xMirror);
            if (yTeleporting) Engine::window->draw(yMirror);
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

    void setXMirror() {

        sf::Vector2f pos = sprite->sprite.getPosition();
        float hProj = getHorizontalProjection();
        xMirror = sprite->sprite;

        _setXTeleporting(hProj, &pos);

        xMirror.setPosition(pos);
    }

    void setYMirror() {

        sf::Vector2f pos = sprite->sprite.getPosition();
        float vProj = getVerticalProjection();
        yMirror = sprite->sprite;

        _setYTeleporting(vProj, &pos);

        yMirror.setPosition(pos);
    }

    void _setXTeleporting(float proj, sf::Vector2f* pos) {

        if (_rightMirror(proj, pos) or _leftMirror(proj, pos)) {

            xTeleporting = true;
        }

        else xTeleporting = false;
    }

    void _setYTeleporting(float proj, sf::Vector2f* pos) {

        if (_upMirror(proj, pos) or _downMirror(proj, pos)) {

            yTeleporting = true;
        }

        else yTeleporting = false;
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