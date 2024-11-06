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
void CollisionHandler::handleShipCollision(const std::shared_ptr<Mesh>& ship, Asteroids& asteroids, Scene& scene) {
    // Reset ship position
    ship->position.set(0, 0, 0);
    ship->visible = true;

    // Clear all asteroids
    asteroids.clearAsteroids(scene);
}


void CollisionHandler::bulletAsteroidCollision(std::vector<std::shared_ptr<Bullet>>& bullets, Asteroids& asteroids, Scene& scene, int& score) {
    std::vector<std::shared_ptr<Bullet>> bulletsToRemove;
    std::vector<std::shared_ptr<Mesh>> asteroidsToRemove;

    // Check for collision between bullets and asteroids
    for (const auto& bullet : bullets) {
        for (const auto& asteroid : asteroids.getAsteroidMeshes()) {
            if (bullet->getMesh()->position.distanceTo(asteroid->position) < collisionDistance) {
                // Mark bullet and asteroid for removal
                bulletsToRemove.push_back(bullet);
                asteroidsToRemove.push_back(asteroid);

                // Update the score
                score += 10;
            }
        }
    }

    // Remove marked bullet from scene and bullets vector
    for (const auto& bullet : bulletsToRemove) {
        if (bullet->getMesh()->parent) {
            scene.remove(*bullet->getMesh());
        }
        bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
    }

    // Remove marked asteroids from the scene and asteroids vector
    for (const auto& asteroid : asteroidsToRemove) {
        if (asteroid->parent) {
            scene.remove(*asteroid);
        }
        asteroids.removeAsteroid(asteroid);
    }
}


