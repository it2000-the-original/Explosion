
class Background {

private:

    std::string background;

    b2BodyDef backDef; // definizione del corpo 

public:

    Background(std::string);

    void drawBackground();

    void drawLine(float, int, int);
};