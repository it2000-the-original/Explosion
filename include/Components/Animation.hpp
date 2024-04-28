#include <map>
#include <string>

#include "AnimationData.hpp"

using Animations = std::map<std::string, ani::AnimationData>;

class Animation : public Component {

private:

    Sprite* sprite;

    Animations animations;

    int frame  = 0; // Frame attuale
    int frames = 1; // Numero di frame
    int index  = 0; // La riga dello spritesheet
    sf::Time speed; // Dirata di un frame

    bool animating = false;

    sf::Clock clock;

public:

    void init();
    void update();

    void addAnimation(std::string n, int i, int f, float s);
    void playAnimation(std::string n);
    void addAndPlay(std::string n, int i, int f, float s);
};