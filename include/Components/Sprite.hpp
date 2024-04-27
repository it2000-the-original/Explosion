// Gestisce un sf::Sprite per la rappresentazione grafica di Body

class Sprite : public Component {

private:

    Body* body;

    bool show = true;

    float width;
    float height;
    float scale;

public:

    sf::Sprite sprite;

	Sprite(Element*);
    Sprite(std::string);

    void init();
    void update();
    void draw();
    void hide(bool);

    float getWidth();
    float getHeight();
    float getScale();
};