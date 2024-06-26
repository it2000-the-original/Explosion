// Questa classe contiene l'algoritmo vero e proprio diguardante la sfida

namespace explosion {

	// Un livello non è altro che una lista di elementi
	// casuali ma aventi più o meno tutti la stessa massa.
	// più si va avanti di livello, più gli oggetti sono
	// numerosi e meno massicci

	using Level  = std::vector<std::string>;
	using Debris = std::vector<Level>;
};

struct ExplosionDef {

	std::string element;

	int frames;  // Frames number
	float speed; // Frame time

	// l'utilizzo dei detriti non è obbligatorio,
	// è possibile lasciarli vuoti per non usarli

	explosion::Debris debris;
	int debrisQuantity;
};

class ExplosionsLoader {

private:

	static const float minImpulse;  // Impulso massimo applicabile ai detriti
	static const float maxImpulse;  // Impulso minimo
	static const float minAImpulse; // Impulso angolare massimo
	static const float maxAImpulse; // Impulso angolare minimo

	static b2BodyDef dBDef;    // Definitione del corpo dei detriti
	static b2BodyDef eBDef;    // Definizione del corpo dell'esplosione
	static b2FixtureDef dFDef; // Fixture dei detriti
	static b2FixtureDef eFDef; // Fixture dell'esplosione

	static void _setDebrisDef();
	static void _setExplosionDef();

	static Entity& _loadDebris(std::string);
	static Entity& _loadExplosion(ExplosionDef);

	static void _launchDebris(std::string, b2Vec2);
	static void _launchExplosion(ExplosionDef, b2Vec2);

public:

	static void init();

	static void loadExplosion(ExplosionDef, b2Vec2);
};