// Questo componente ha lo scopo di distruggere un'entità
// dopo un tempo specifico, la uso per i lasere e per
// i detriti degli asteroidi

class Destroyer : public Component {

private:

    Sprite* sprite;

    sf::Time time;
    sf::Clock clock;

	bool transition;

    void setTransparency();

public:

    Destroyer(float _time, bool _trans = true);

    void init();
    void update();
};