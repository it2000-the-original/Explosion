#include "Asset.hpp"

const std::vector<Asset> assets = {

    {"assets/textures/playerShip3_blue.png", "player", 98, 75, 0.5f, 
    
    // La navicella

    {
        {62,0},{98,8},{98,16},{52,76},
        {46,76},{-2,16},{-2,8},{34,0}
    }},

    {"assets/textures/meteorBrown_big3.png", "meteor", 89, 82, 0.5f,

    // L'asteroide

    {
        {66,0},{88,40},{72,70},{34,82},
        {0,60},{2,26},{18,6}
    }},

    {"assets/textures/black.png",            "background", 256, 256, 0.5f},
    {"assets/textures/laserBlue16.png",      "laser",      13,  54,  0.5f},
    {"assets/textures/meteorBrown_big3.png", "meteor1",    89,  82,  0.125f},  // Detrito 1
    {"assets/textures/meteorBrown_big3.png", "meteor2",    89,  82,  0.0625f}, // Detrito 2
};