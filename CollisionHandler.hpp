#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP

#include "Asteroids.hpp"
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

    // Handles collision effect (explosion)
    static void handleCollision(const std::shared_ptr<Mesh>& ship, Asteroids& asteroids, Scene& scene);

private:
    float collisionDistance;    // Distance collision is detected at
};



#endif //COLLISIONHANDLER_HPP
