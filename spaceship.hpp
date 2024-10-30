#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Spaceship {
public:
    Spaceship();

    void rotateLeft();
    void rotateRight();
    void moveForward();
    std::shared_ptr<Mesh> getMesh() const;

private:
    std::shared_ptr<Mesh> spaceshipMesh;
    float spaceshipRotation;
    float spaceshipRotationSpeed;
    float spaceshipForwardSpeed;

    void updateRotation();
    void wrapAround(Vector3& position);
};

#endif //SPACESHIP_HPP
