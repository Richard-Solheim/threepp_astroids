#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "threepp/threepp.hpp"
#include "MovementController.hpp"
#include <memory>

using namespace threepp;

class Spaceship {
public:
    // Constructor to initialize the spaceship geometry and boundaries
    Spaceship(float boundaryX, float boundaryY);

    // Methods for controlling spaceship movement
    void rotateLeft();      // Rotate counterclockwise
    void rotateRight();     // Rotate clockwise
    void moveForward();     // Move forward in direction it's facing
    void update();          // Updates spaceship movement and physics

    // Provides access to spaceships mesh so it can be added to scene
    std::shared_ptr<Mesh> getMesh() const;

private:
    std::shared_ptr<Mesh> mesh;                 // 3d object representing ship
    MovementController movementController;      // Handles spaceships movement logic
    float rotationSpeed;                        // Speed ship rotates with
    float acceleration;                         // Adds acceleration
    float friction;                             // Adds friction
    float maxSpeed;                             // Adds max speed

    // Internal helpers for updating rotation and screen wrapping
    void updateRotation();              // Applies the current rotation to the mesh
};

#endif //SPACESHIP_HPP
