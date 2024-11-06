#include "spaceship.hpp"
#include <cmath>

using namespace threepp;


// Constructor: initializes the spaceship's geometry, color, and initial values
Spaceship::Spaceship(float boundaryX, float boundaryY)
            : rotationSpeed(0.05f), acceleration(0.01f), friction(0.99f), maxSpeed(0.2f),
              movementController(nullptr, boundaryX, boundaryY) {

    // Load PNG as model
    auto textureLoader = TextureLoader();
    auto texture = textureLoader.load("models/spaceship.png");

    // Create a geometry to display texture
    auto geometry = PlaneGeometry::create(3.0f, 3.0f);
    auto material = MeshBasicMaterial::create();
    material->map = texture;
    material->transparent = true;

    // Create mesh for the spaceship
    mesh = Mesh::create(geometry, material);

    // Set initial position
    mesh->position.set(0,0,0);

    // Initialize the movement controller with the spaceship mesh
    movementController = MovementController(mesh, boundaryX, boundaryY);
}

// Accessor method to retrieve the mesh object (for adding to the scene)
std::shared_ptr<Mesh> Spaceship::getMesh() const {
    return mesh;
}

// Rotates the spaceship to the left (clockwise)
void Spaceship::rotateLeft() {
    movementController.rotateLeft(rotationSpeed);
}

// Rotates the spaceship to the right (counterclockwise)
void Spaceship::rotateRight() {
    movementController.rotateRight(rotationSpeed);
}

// Moves spaceship forward in facing direction
void Spaceship::moveForward() {
    movementController.moveForward(acceleration);
}

void Spaceship::update() {
    movementController.update(friction, maxSpeed);
}