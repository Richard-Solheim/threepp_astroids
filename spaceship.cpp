#include "spaceship.hpp"

using namespace threepp;

// Initialize spaceship with default values
Spaceship::Spaceship() : x(0), y(0), velocityX(0), velocityY(0), rotation(0) {}

// Move spaceship based on velocity
void Spaceship::move() {
    x += velocityX;     // Update X based on velocity in X direction
    y += velocityY;     // Update Y based on velocity in Y direction
}

// Rotates spaceship by adding the angle to current location
void Spaceship::rotate(float angle) {
    rotation += angle;  // Adjust rotation angle
}

// Sets the velocity for the spaceship (speed in X and Y direction)
void Spaceship::setVelocity(float vx, float vy) {
    velocityX = vx;
    velocityY = vy;
}

// Returns current position
void Spaceship::getPosition(float& posX, float& posY) {
    posX = x;
    posY = y;
}

// Returns current angle
float Spaceship::getRotation() const {
    return rotation;
}

