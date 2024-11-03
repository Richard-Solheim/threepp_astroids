#include "Asteroids.hpp"

#include <random>
#include <math.h>

Asteroids::Asteroids(int maxAsteroids, float spawnRange)
    : maxAsteroids(maxAsteroids), spawnRange(spawnRange) {
    // Gives asteroid random rotation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize list with max number asteroids
    asteroids.reserve(maxAsteroids);
    asteroidMeshes.reserve(maxAsteroids);

}

// Spawns a new asteroid within specified range around spaceship
void Asteroids::spawnAsteroid(const Vector3& spaceshipPosition) {
    auto asteroid = std::make_shared<Asteroid>(spawnRange, spawnRange);

    // Position at random point within spawnrange
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> angleDis(0.0f, 2.0f * M_PI);
    std::uniform_real_distribution<float> distanceDis(spawnRange, spawnRange + 15.0f);  // Adjust after need

    // Calculate random position at a given distance from ship
    float angle = angleDis(gen);
    float distance = distanceDis(gen);
    asteroid->getMesh()->position.set(
        spaceshipPosition.x + distance * cos(angle),
        spaceshipPosition.y + distance * sin(angle),
        0.0f
    );

    asteroids.push_back(asteroid);
    asteroidMeshes.push_back(asteroid->getMesh());
}

// Updates all asteroids and removes those outside spawn range, then spawn new ones
void Asteroids::update(const Vector3 &spaceshipPosition) {
    for (auto it = asteroids.begin(); it != asteroids.end();) {
        auto& asteroid = *it;
        asteroid->update();

        // Remove faded out asteroids
        if (asteroid->isFadedOut()) {
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

// Clears all current asteroids from the scene
void Asteroids::clearAsteroids(Scene &scene) {
    for (auto& asteroid: asteroids) {
        auto mesh = asteroid->getMesh();

        // Apply a fade out to remove asteroid meshes from the scene
        auto material = mesh->material()->as<MeshBasicMaterial>();
        material->transparent = true;// Transparency enabled
        material->opacity = 1.0f;    // Start at full opacity

        // Apply fade out loop
        while (material->opacity > 0.0f) {
            material->opacity -= 0.1f;// Reduce opacity over time
            mesh->updateMatrixWorld();// Update mesh state
        }

        // Remove mesh from scene
        if (mesh->parent) {
            scene.remove(*mesh);
        }
    }
    asteroids.clear();
    asteroidMeshes.clear();
}
void Asteroids::removeAsteroid(const std::shared_ptr<Mesh>& asteroid) {
    asteroidMeshes.erase(std::remove(asteroidMeshes.begin(), asteroidMeshes.end(), asteroid), asteroidMeshes.end());
}

// Return all asteroid meshes
const std::vector<std::shared_ptr<Mesh>>& Asteroids::getAsteroidMeshes() const {
    return asteroidMeshes;
}

