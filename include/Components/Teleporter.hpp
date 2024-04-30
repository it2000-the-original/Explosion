// Questo componente ha la funzione di fare da effetto
// pacman, quando ci si trova al bordo dello schermo,
// si viene trasportati dall'altro lato

class Teleporter : public Component {

private:

    Body* body;

	void teleport();

    float getHorizontalProjection();
    float getVerticalProjection();

public:

    void init();
    void update();
};