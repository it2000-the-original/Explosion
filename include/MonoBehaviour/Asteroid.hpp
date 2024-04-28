// Questa classe contiene l'algoritmo vero e proprio

using Level = std::vector<std::string>;

class Asteroid : public MonoBehaviour {

private:

	Body* body;

    bool exp = false; // Se true, l'asteroide esploderà

    const int number = 3; // Numero dei rottami da scagliare

    const float minImpulse  = 0.01;   // Impulso da applicare (su base 1000)
    const float maxImpulse  = 0.05;   // Possibile variazione dell'impulso (su base 1000)
    const float minAImpulse = -0.001;
    const float maxAImpulse = +0.001;

	b2BodyDef    bodyDef;
	b2FixtureDef fixtureDef;

    std::vector<Level> levels;

	void launchDebris(Element* element);
	void launchExplosion(Element* element);

    Entity& loadDebris(Element* element);
	Entity& loadExplosion(Element* element);

    void setBodyDef();
	void setFixtureDef();
	void setLevels();

	auto getExplosionBodyDef()    const -> b2BodyDef;
	auto getExplosionFixtureDef() const -> b2FixtureDef;

public:

	Asteroid();

	void init();
    void update();
    void explode();
    void onCollision2D(Entity*);
};