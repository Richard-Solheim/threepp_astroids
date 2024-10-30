#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

// Manages multiple asteroids in the scene, like spawning, updating and removing them

#include "Asteroid.hpp"
#include <vector>

class Asteroids {
public:
    // Constructor: Initialize asteroid manager with boundary and max number
    Asteroids(int maxAsteroids, float spawnRadius, float despawnRadius);

    // Updates all asteroids and respawning new
    void update(const Vector3& spaceshipPosition);

    // Returns all asteroid meshes
    const std::vector<std::shared_ptr<Mesh>> &getAsteroidMeshes() const;

private:
    int maxAsteroids;                                    // Max asteroids allowed at once
    float spawnRadius, despawnRadius;                    // Radius where asteroids spawn and despawn
    std::vector<std::shared_ptr<Asteroid>> asteroids;    // List of active asteroids
    std::vector<std::shared_ptr<Mesh>> asteroidMeshes;   // List of asteroid meshes

    // Spawns new asteroid within specified radius from spaceship
    void spawnAsteroid(const Vector3& spaceshipPosition);
};



#endif //ASTEROIDS_HPP
