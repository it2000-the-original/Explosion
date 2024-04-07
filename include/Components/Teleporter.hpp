
struct Teleporter {

    sf::Sprite sprite;

    void update(b2Body* body) {

        teleport(body);
    }

    void teleport(b2Body* body) {

        b2Vec2 position = body->GetPosition();

        if (position.x >= float(windowWidth) / WS or position.x < 0.f or
            position.y >= float(windowHeight) / WS or position.y < 0.f) {

            position.x = float(windowWidth) / WS - position.x;
            position.y = float(windowHeight) / WS - position.y;
        }

        body->SetTransform(position, body->GetAngle());
    }
};