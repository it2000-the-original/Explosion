// Questo componente ha la funzione di fare da effetto
// pacman, quando ci si trova al bordo dello schermo,
// si viene trasportati dall'altro lato

class Teleporter : public Component {

private:

    Body* body;
    Sprite* sprite;

    bool mirror; // Stabilisce se disegnare lo specchio o no

    sf::Sprite xMirror; // Specchio per la proiezione orizzontale
    sf::Sprite yMirror; // Specchio per la proiezione verticale

    bool xTeleporting = false;
    bool yTeleporting = false;

	void teleport();
    void setXMirror();
    void setYMirror();

    void setXTeleporting(float proj, sf::Vector2f* pos);
    void setYTeleporting(float proj, sf::Vector2f* pos);

    float getHorizontalProjection();
    float getVerticalProjection();

    bool rightMirror(float proj, sf::Vector2f* pos);
    bool leftMirror (float proj, sf::Vector2f* pos);
    bool downMirror (float proj, sf::Vector2f* pos);
    bool upMirror   (float proj, sf::Vector2f* pos);

public:

    Teleporter(bool _mirror = true);

    void init();
    void update();
    void draw();
};