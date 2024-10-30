#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

class Spaceship {
public:
    // Constructor to initialize the spaceship geometry and boundaries
    Spaceship(float boundaryX, float boundaryY);

    // Methods for controlling spaceship movement
    void rotateLeft();      // Rotate counterclockwise
    void rotateRight();     // Rotate clockwise
    void moveForward();     // Move forward in direction it's facing

    // Provides access to spaceships mesh so it can be added to scene
    std::shared_ptr<Mesh> getMesh() const;

private:
    std::shared_ptr<Mesh> mesh;    // 3d object representing ship
    float rotation;                // Current rotation angle in radians
    float rotationSpeed;           // Speed ship rotates with
    float forwardSpeed;            // Speed ship moves forward with

    // Boundary limits for movement
    float minX, maxX;   // X boundaries
    float minY, maxY;   // Y boundaries

    // Internal helpers for updating rotation and screen wrapping
    void updateRotation();              // Applies the current rotation to the mesh
};

#endif //SPACESHIP_HPP
