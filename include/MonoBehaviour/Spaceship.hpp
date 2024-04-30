
class Spaceship : public MonoBehaviour {

private:

    Body* body;

    Entity* flame;

    const float boost = 0.3f;       // Forza applicata per il movimento in avanti
    const float torsion = 0.025f;   // Forza di rotazione applicata dai comandi
    const float rdamping = 0.0125;  // Questa attrito viene applicata solo quando non vi sono comandi di rotazione
    const float fDinstance = 0.27f; // Distanza che la fiamma deve avere dal retro della navicella

    void moveForward();
    void rotateRight();
    void rotateLeft();
    void slowsRightRotation();
    void slowsLeftRotation();

    auto getFlameBodyDefinition()    -> b2BodyDef;
    auto getFlameFixtureDefinition() -> b2FixtureDef;

    void loadFlame();
    void setFlameAnimations();
    void setFlamePosition();

public:

    void init();
    void update();
};