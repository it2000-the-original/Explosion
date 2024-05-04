// Questo componente ha lo scopo di distruggere un'entità
// dopo un tempo specifico, la uso per i laser e per
// i detriti degli asteroidi

class Destroyer : public Component {

private:

    Sprite* sprite;

    sf::Time time;   // Durata dell'oggetto prima della distruzione
    sf::Clock clock;

	bool transition;

    void setTransparency();

public:

    Destroyer(float, bool = true);

    void init();
    void update();
};