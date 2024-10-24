#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "threepp/threepp.hpp"
using namespace threepp;

class Spaceship {
private:
    // Variable for position and velocity
    float x, y;         // Position of spaceship
    float velocityX;    // Velocity along x-axis
    float velocityY;    // Velocity along y-axis
    float rotation;     // Rotation angle of the spaceship

public:
    // Constructor
    Spaceship();

    // Moving the spaceship based on velocity
    void move();

    // Rotating spaceship
    void rotate(float angle);

    // Setting velocity
    void setVelocity(float vx, float vy);

    // Get current position
    void getPosition(float& posX, float& posY) const;

    // Get current rotation
    float getRotation() const;
};

#endif //SPACESHIP_HPP
