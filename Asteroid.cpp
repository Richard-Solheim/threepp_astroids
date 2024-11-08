#include "Asteroid.hpp"
#include <random>
#include <ctime>

using namespace threepp;

// Constructor: Initializes an asteroid outside play area with random diraction
Asteroid::Asteroid(float boundaryX, float boundaryY) : speed(0.1f), opacity(1.0f) {
    // // Seed for random rotation on model
    // std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Load PNG model
    auto textureLoader = TextureLoader();
    auto texture = textureLoader.load("models/Asteroid.png");

    // Create a plane geometry to display the texture
    auto geometry = PlaneGeometry::create(5.0f, 5.0f);
    auto material = MeshBasicMaterial::create();
    material->map = texture;
    material->transparent = true;
    material->opacity = opacity;

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

    // Check if asteroid should start fading
    if (std::abs(mesh->position.x) > 90.0f || std::abs(mesh->position.y) > 90.0f) {     // Adjust value after need
        if (opacity > 0) {
            opacity -= 0.02f;       // Adjust value for faster or slower fading
            mesh->material()->as<MeshBasicMaterial>()->opacity = opacity;
        }
    }
}

// Checks if asteroid is out of bounds
bool Asteroid::isFadedOut() const {
    return opacity <= 0.0f;
}

// Accessor for asteroid mesh
std::shared_ptr<Mesh> Asteroid::getMesh() const {
    return mesh;
}
