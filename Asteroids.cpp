#include "Asteroids.hpp"

#include <random>
#include <math.h>

Asteroids::Asteroids(int maxAsteroids, float spawnRadius, float despawnRadius)
    : maxAsteroids(maxAsteroids), spawnRadius(spawnRadius), despawnRadius(despawnRadius) {
    // Initialize list with max number asteroids
    asteroids.reserve(maxAsteroids);
    asteroidMeshes.reserve(maxAsteroids);
}

// Spawns a new asteroid within specified radius of spaceship
void Asteroids::spawnAsteroid(const Vector3 &spaceshipPosition) {
    auto asteroid = std::make_shared<Asteroid>(spawnRadius, despawnRadius);

    // Position outside spaceship spawn radius
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDis(0.0f, 2.0f * M_PI);

    // Randomize the asteroids spawn position around spaceship
    float angle = angleDis(gen);
    asteroid->getMesh()->position.set(
        spaceshipPosition.x + spawnRadius * cos(angle),
        spaceshipPosition.y + spawnRadius * sin(angle),
        0.0f
    );
}

// Updates all asteroids and removes those out of bounds, then spawn new ones
void Asteroids::update(const Vector3 &spaceshipPosition) {
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        auto &asteroid = *it;
        asteroid->update();

        // Check if asteroid is outside radius
        if (asteroid->getMesh()->position.distanceTo(spaceshipPosition) > despawnRadius) {
            // Remove out of bounds from lists
            asteroidMeshes.erase(std::remove(asteroidMeshes.begin(), asteroidMeshes.end(), asteroid->getMesh()), asteroidMeshes.end());
            it = asteroids.erase(it);

            // Spawn a new asteroid within spawn radius
            spawnAsteroid(spaceshipPosition);
        } else {
            ++it;
        }
    }

    // Ensure enough asteroids are in play
    while (asteroids.size() < maxAsteroids) {
        spawnAsteroid(spaceshipPosition);
    }

}

// Return all asteroid meshes
const std::vector<std::shared_ptr<Mesh>> &Asteroids::getAsteroidMeshes() const {
    return asteroidMeshes;
}

