#include <string>

struct Asset {

    std::string path; // Destinazione della texture
    std::string name; // Nome dell'elemento
    int width;
    int height;
    float scale; // Fattore di scala

    std::vector<sf::Vector2i> shape; // Poligono di collisione
};