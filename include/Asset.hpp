#include <string>

struct Asset {

    std::string path;
    std::string name;
    int width;
    int height;
    float scale;

    std::vector<sf::Vector2i> shape;
};