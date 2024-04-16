// Questo componente ha lo scopo di distruggere un'entità
// dopo un tempo specifico, la uso per i lasere e per
// i detriti degli asteroidi

class Destroyer : public Component {

private:

    Sprite* sprite;

    sf::Time time;
    sf::Clock clock;

public:

    Destroyer(float seconds) {

        time = sf::seconds(seconds);
    }

    void init() {

        sprite = &entity->getComponent<Sprite>();
        clock.restart();
    }

    void update() {

        setTransparency();

        if (clock.getElapsedTime() >= time) {

            entity->destroy();
        }
    }

    void setTransparency() {

        // Questa funzione imposta la strasparenza di uno sprite
        // man mano che il tempo rimasto diminuisce, usando una semlice proporzione

        auto color = sprite->sprite.getColor();
        float remainTime = time.asSeconds() - clock.getElapsedTime().asSeconds();
        color.a = 255 * remainTime / time.asSeconds();
        sprite->sprite.setColor(color);
    }
};