// Questo componente di occupa di gestire l'arma della
// navicella, e di caricare nella giusta posizione, tutte
// le entità riguardanti i raggi laser

class Weapon : public Component {

private:

    Body* body;

    const float velocity = 10.f;

    std::string element; // Elemento del laser

    bool fired = false; // per evitare problemi nel caso si tenesse premuta la spacebar

	Entity& loadLaser();

	auto getBodyDef()    -> b2BodyDef;
	auto getFixtureDef() -> b2FixtureDef;

public:

    Weapon(std::string);

    void init();
    void update();
    void shoot();
};