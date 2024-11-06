#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "Asteroids.hpp"
#include "Bullet.hpp"
#include "threepp/threepp.hpp"
#include <memory>
#include <vector>

using namespace threepp;

class CollisionHandler {
public:
    //Constructor
    CollisionHandler(float collisionDistance);

    // Check for collision between spaceship and the list of asteroids
    bool checkCollision(const std::shared_ptr<Mesh>& ship, const std::vector<std::shared_ptr<Mesh>>& asteroids);

    // Handles collision between the ship and an asteroid
    static void handleShipCollision(const std::shared_ptr<Mesh>& ship, Asteroids& asteroids, Scene& scene);

    // Check for collision between bullet and asteroid
    void bulletAsteroidCollision(std::vector<std::shared_ptr<Bullet>>& bullets, Asteroids& asteroids, Scene& scene, int& score);

private:
    float collisionDistance;    // Distance collision is detected at
};



#endif //COLLISIONHANDLER_HPP
