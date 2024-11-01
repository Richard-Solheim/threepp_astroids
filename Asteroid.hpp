#ifndef ASTEROID_HPP
#define ASTEROID_HPP
#include <memory>

#include "threepp/threepp.hpp"
using namespace threepp;

class Asteroid {
public:
    // Constructor initializes an asteroid outside the play area with a random direction
    Asteroid(float boundaryX, float bounadryY);

    // Updates the asteroids position based on direction and speed
    void update();

    // Checks if asteroid is out of bounds
    bool isFadedOut() const;

    // Accessor for the asteroid mesh, so it can be added to scene
    std::shared_ptr<Mesh> getMesh() const;

private:
    std::shared_ptr<Mesh> mesh;     // Mesh representing asteroid
    Vector3 direction;              // Direction vector for movement
    float speed;                    // Speed of the asteroid
    float opacity;                  // Current opacity
};



#endif //ASTEROID_HPP
