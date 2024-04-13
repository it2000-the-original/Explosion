#include <SFML/Graphics.hpp>

struct Element {

    sf::Texture texture;
    float width;
    float height;
    float scale;

    b2PolygonShape shape;
};