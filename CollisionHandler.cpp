#include "CollisionHandler.hpp"

#include <iostream>

// Constructor: Initializes the collision handler with specified collision distance
CollisionHandler::CollisionHandler(float collisionDistance) : collisionDistance(collisionDistance) {}

// Check for collision between spaceship and the list of asteroids
bool CollisionHandler::checkCollision(const std::shared_ptr<Mesh>& ship, const std::vector<std::shared_ptr<Mesh>>& asteroids) {
    for (const auto& asteroid : asteroids) {
        if (ship->position.distanceTo(asteroid->position) < collisionDistance) {
            return true;    // Collision detected
        }
    }
    return false;           // No collision detected
}

// Handles collision effect (explosion)
void CollisionHandler::handleCollision(const std::shared_ptr<Mesh>& ship, Asteroids& asteroids, Scene& scene) {
    // Reset ship position
    ship->position.set(0, 0, 0);
    ship->visible = true;

    // Clear all asteroids
    asteroids.clearAsteroids(scene);
}




