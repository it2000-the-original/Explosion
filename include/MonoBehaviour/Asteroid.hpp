// Questa classe contiene l'algoritmo vero e proprio

class Asteroid : public MonoBehaviour {

private:

	Body* body;

    bool exp = false; // Se true, l'asteroide esploderà

public:

	void init();
    void update();
    void onCollision2D(Entity*);

    void explode();
};