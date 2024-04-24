#include <map>
#include <string>

using Animations = std::map<std::string, ani::AnimationData>;

class Animation : public Component {

private:

    Sprite* sprite;

    Animations animations;

    int index = 0;
    int frames = 1;
    sf::Time speed;

    int frame = 0;

    bool animating = false;

    sf::Clock clock;

public:

    void addAnimation(std::string name, int i, int f, int s) {

        ani::AnimationData ani(i, f, s);
        animations.emplace(name, ani);
    }

    void playAnimation(std::string name) {

        index = animations[name].index;
        frames = animations[name].frames;
        speed = sf::milliseconds(animations[name].speed);

        animating = true;
        clock.restart();
    }

    void init() {

        sprite = &entity->getComponent<Sprite>();
    }

    void update() {

        if (animating and clock.getElapsedTime() >= speed) {

            frame = (frame + 1) % frames;

            sf::IntRect rect(
                sprite->width  / sprite->scale * frame,
                sprite->height / sprite->scale * index,
                sprite->width  / sprite->scale,
                sprite->height / sprite->scale
            );

            sprite->sprite.setTextureRect(rect);

            clock.restart();
        }
    }
};