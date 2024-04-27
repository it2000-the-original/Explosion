// Questa classe contiene l'algoritmo vero e proprio

using Level = std::vector<std::string>;

class Asteroid : public MonoBehaviour {

private:

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

    Entity& loadDebris(Element* element);

    void setBodyDef();
	void setFixtureDef();
	void setLevels();

public:

	Asteroid();

    void update();
    void explode();
    void onCollision2D(Entity*);
};