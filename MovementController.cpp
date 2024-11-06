#include "MovementController.hpp"
#include <cmath>

// Constructor: Initializes the controller with a mesh and boundaries of the map
MovementController::MovementController(std::shared_ptr<Mesh> mesh, float playAreaX, float playAreaY)
    : mesh(mesh), maxX(playAreaX), maxY(playAreaY), minX(-playAreaX), minY(-playAreaY), velocity(0, 0, 0) {}

// Rotate counterclockwise
void MovementController::rotateLeft(float rotationSpeed) {
    mesh->rotation.z += rotationSpeed;
}

// Rotate clockwise
void MovementController::rotateRight(float rotationSpeed) {
    mesh->rotation.z -= rotationSpeed;
}

// Move forward in facing direction
void MovementController::moveForward(float acceleration) {
    Vector3 direction(-std::sin(mesh->rotation.z), std::cos(mesh->rotation.z), 0);
    velocity += direction * acceleration;
}

// Update object position
void MovementController::update(float friction, float maxSpeed) {
    // Apply friction
    velocity = velocity * friction;

    // Limit velocity to max speed
    if (velocity.length() > maxSpeed) {
        velocity.normalize();               // Keep same direction
        velocity = velocity * maxSpeed;     // Set magnitude to max speed
    }

    mesh->position = mesh->position + velocity;

    // Wrap object within boundaries
    if (mesh->position.x > maxX) {mesh->position.x = minX;}     // Checks if out on positive X and moves to start of negative X
    if (mesh->position.x < minX) {mesh->position.x = maxX;}     // Checks if out on negative X and moves to start of positive X
    if (mesh->position.y > maxY) {mesh->position.y = minY;}     // Checks if out on positive Y and moves to start of negative Y
    if (mesh->position.y < minY) {mesh->position.y = maxY;}     // Checks if out on negative Y and moves to start of positive Y
}
