#include "Spaceship.hpp"
#include <iostream>

int main() {
    Spaceship spaceship;

    // Set initial velocity (move right at speed 1.0, and no movement in Y direction)
    spaceship.setVelocity(1.0f, 0.0f);

    // Move the spaceship in the game loop
    spaceship.move();

    // Get the updated position
    float x, y;
    spaceship.getPosition(x, y);

    std::cout << "Spaceship position: (" << x << ", " << y << ")\n";

    // Rotate the spaceship by 15 degrees
    spaceship.rotate(15.0f);

    // Get the updated rotation
    std::cout << "Spaceship rotation: " << spaceship.getRotation() << " degrees\n";

    return 0;
}
