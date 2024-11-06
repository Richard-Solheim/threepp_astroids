#ifndef MOVEMENTCONTROLLER_HPP
#define MOVEMENTCONTROLLER_HPP

#include "threepp/threepp.hpp"
#include <memory>

using namespace threepp;

class MovementController {
public:
    // Constructor: Initializes the controller with a mesh and boundaries of the map
    MovementController(std::shared_ptr<Mesh> mesh, float playAreaX, float playAreaY);

    // Rotation and movement
    void rotateLeft(float rotationSpeed);           // Rotate counterclockwise
    void rotateRight(float rotationSpeed);          // Rotate clockwise
    void moveForward(float acceleration);           // Move forward in facing direction

    void update(float friction, float maxSpeed);    // Update object position

private:
    std::shared_ptr<Mesh> mesh;     // Object representing the ship
    Vector3 velocity;               // Current velocity
    float maxX;                     // Boundary of map in x direction
    float maxY;                     // Boundary of map in y direction
    float minX;                     // Boundary of map in -x direction
    float minY;                     // Boundary og map in -y direction
};



#endif //MOVEMENTCONTROLLER_HPP
