#ifndef BULLET_HPP
#define BULLET_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Bullet {
public:
    // Constructor: Initializes bullet with position and direction
    Bullet(const Vector3& position, const Vector3& direction);

    // Updates the bullets position
    void update();

    // Checks if bullet is out of bounds
    bool isOutOfBounds(float boundaryX, float boundaryY) const;

    // Access bullet mesh
    std::shared_ptr<Mesh> getMesh() const;

private:
    std::shared_ptr<Mesh> mesh;     // Mesh representing bullet
    Vector3 direction;              // Direction vector is moving
    float speed;                    // Speed of bullet
};



#endif //BULLET_HPP
