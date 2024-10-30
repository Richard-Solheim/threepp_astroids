//
// Created by Richa on 30.10.2024.
//

#include "Asteroids.hpp"

Asteroids::Asteroids(int maxAsteroids, float boundaryX, float boundaryY)
    : maxAsteroids(maxAsteroids), boundaryX(boundaryX), boundaryY(boundaryY) {
    // Initially spawn max number asteroids
    for (int i = 0; i < maxAsteroids; i++) {
        auto asteroid = std::make_shared<Asteroid>(boundaryX, boundaryY);
        asteroids.push_back(asteroid);
        asteroidMeshes.push_back(asteroid->getMesh());
    }
}

// Updates all asteroids and removes those out of bounds, then spawn new ones
void Asteroids::update() {
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        auto &asteroid = *it;
        asteroid->update();

        // Remove asteroids that go out of bounds
        if (asteroid->isOutOfBounds(boundaryX, boundaryY)) {
            // Remove from mesh list and asteroid list
            asteroidMeshes.erase(std::remove(asteroidMeshes.begin(), asteroidMeshes.end(), asteroid->getMesh()), asteroidMeshes.end());
            it = asteroids.erase(it);

            // Respawn new asteroid
            auto newAsteroid = std::make_shared<Asteroid>(boundaryX, boundaryY);
            asteroids.push_back(newAsteroid);
            asteroidMeshes.push_back(newAsteroid->getMesh());
        } else {
            ++it;
        }
    }
}

// Return all asteroid meshes
const std::vector<std::shared_ptr<Mesh>> &Asteroids::getAsteroidMeshes() const {
    return asteroidMeshes;
}

