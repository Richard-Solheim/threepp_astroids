#include "spaceship.hpp"
#include <cmath>

using namespace threepp;


// Constructor: initializes the spaceship's geometry, color, and initial values
Spaceship::Spaceship(float boundaryX, float boundaryY)
            : rotation(0.0f), rotationSpeed(0.05f), acceleration(0.01f), friction(0.99f), maxSpeed(0.2f),
              minX(-boundaryX), maxX(boundaryX), minY(-boundaryY), maxY(boundaryY) {

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
}

// Accessor method to retrieve the mesh object (for adding to the scene)
std::shared_ptr<Mesh> Spaceship::getMesh() const {
    return mesh;
}

// Rotates the spaceship to the left (clockwise)
void Spaceship::rotateLeft() {
    rotation += rotationSpeed;  // Increase rotation angle
    updateRotation();           // Apply new rotation to mesh
}

// Rotates the spaceship to the right (counterclockwise)
void Spaceship::rotateRight() {
    rotation -= rotationSpeed;  // Decrease rotation angle
    updateRotation();           // Apply new rotation to mesh
}

// Moves spaceship forward in facing direction
void Spaceship::moveForward() {
    // calculate the movement direction based on current rotation
    Vector3 direction(std::sin(-rotation), std::cos(rotation), 0);
    velocity += direction * acceleration;
}

void Spaceship::update() {
    // Apply friction to gradually reduce velocity
    velocity *= friction;

    // Limit speed to max speed
    if (velocity.length() > maxSpeed) {
        velocity.normalize();       // Keep same direction
        velocity *= maxSpeed;       // Set magnitude to max speed
    }

    // Calculate new position components
    mesh->position += velocity;

    // Keep ship inside area
    if (mesh->position.x > maxX) {mesh->position.x = minX;}
    if (mesh->position.x < minX) {mesh->position.x = maxX;}
    if (mesh->position.y > maxY) {mesh->position.y = minY;}
    if (mesh->position.y < minY) {mesh->position.y = maxY;}
}


// Updates spaceship visual rotation by applying current angle to mesh
void Spaceship::updateRotation() {
    mesh->rotation.z = rotation;    // Set rotation of mesh to current angle
}

