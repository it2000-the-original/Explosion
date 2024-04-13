
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

        auto color = sprite->sprite.getColor();
        float remainTime = time.asSeconds() - clock.getElapsedTime().asSeconds();
        color.a = 255 * remainTime / time.asSeconds();

        sprite->sprite.setColor(color);

        if (clock.getElapsedTime() >= time) {

            entity->destroy();
        }
    }
};