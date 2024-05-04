// Questo componente gestisce un corpo della libreria Box2D

class Body : public Component {

private:

    int16 category; // la categoria dell'oggetto

	b2Vec2 size;  // dimensioni dell'oggetto
    b2Body* body;

public:

    Body(b2BodyDef);
    Body(b2BodyDef, b2FixtureDef);

    void init();

	void setSize(b2Vec2);
    void setFixture(b2FixtureDef);
    void setRotation(float);
    void setPosition(b2Vec2);
    void setVelocity (float v, float a);
    void applyForce  (float f, float a);
    void applyImpulse(float i, float a);
    void applyTorque(float);
    void applyAngularImpulse(float);

	auto getSize()      -> b2Vec2;
    auto getPosition()  -> b2Vec2;
    auto getRotation()  -> float;
    auto getVelocity()  -> float;
    auto getRVelocity() -> float;
    auto getCategory()  -> int16;

    ~Body();
};