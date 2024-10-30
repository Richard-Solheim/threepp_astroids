#include "Asteroid.hpp"
#include <random>

using namespace threepp;

// Constructor: Initializes an asteroid outside play area with random diraction
Asteroid::Asteroid(float boundaryX, float boundaryY) : speed(0.1f) {
    // Create a simple sphere to represent asteroid
    auto geometry = SphereGeometry::create(1.0f, 8, 8);
    auto material = MeshBasicMaterial::create();
    material->color = Color::gray;

    mesh = Mesh::create(geometry, material);

    // Set up random starting position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDis(-1.0f, 1.0f);
    std::uniform_real_distribution<float> angleDis(0.0f, 2.0f * M_PI);

    // Decide randomly what side the asteroid will spawn at
    float angle = angleDis(gen);
    mesh->position.set(boundaryX * std::cos(angle), boundaryY * std::sin(angle), 0);

    // Set random direction for movement
    direction.set(posDis(gen), posDis(gen), 0).normalize();   // Normalize for consistent movement
}

// Updates asteroid position based on direction and speed
void Asteroid::update() {
    mesh->position += direction * speed;   // Move asteroid in direction based on speed
}

// Checks if asteroid is out of bounds
bool Asteroid::isOutOfBounds(float boundaryX, float boundaryY) const {
    return std::abs(mesh->position.x) > boundaryX || std::abs(mesh->position.y) > boundaryY;
}

// Accessor for asteroid mesh
std::shared_ptr<Mesh> Asteroid::getMesh() const {
    return mesh;
}
