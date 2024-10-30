#include "spaceship.hpp"
#include <cmath>

using namespace threepp;


// Constructor: initializes the spaceship's geometry, color, and initial values
Spaceship::Spaceship() : rotation(0.0f), rotationSpeed(0.05f), forwardSpeed(0.2f) {

    // Define the triangle shape vertices for the spaceship
    auto geometry = BufferGeometry::create();
    std::vector<float> vertices = {
        0.0f, 1.0f, 0.0f,      // Tip of triangle (front)
        -1.0f, -1.0f, 0.0f,    // Bottom left corner
        1.0f, -1.0f, 0.0f      // Bottom right corner
    };
    geometry->setAttribute("position", FloatBufferAttribute::create(vertices, 3));

    // Create a basic material for the spaceship with color
    auto material = MeshBasicMaterial::create();
    material->color = Color::darkred;

    // Create the mesh from the geometry and material
    mesh = Mesh::create(geometry, material);
    mesh->position.set(0, 0, 0);
}

// Accessor method to retrieve the mesh object (for adding to the scene)
std::shared_ptr<Mesh> Spaceship::getMesh() const {
    return mesh;
}

// Rotates the spaceship to the left (counterclockwise)
void Spaceship::rotateLeft() {
    rotation -= rotationSpeed;  // Decrease rotation angle
    updateRotation();           // Apply new rotation to mesh
}
// Rotates the spaceship to the right (clockwise)
void Spaceship::rotateRight() {
    rotation += rotationSpeed;  // Increase rotation angle
    updateRotation();           // Apply new rotation to mesh
}

// Moves spaceship forward in facing direction
void Spaceship::moveForward() {
    // calculate the movement direction based on current rotation
    Vector3 direction(std::sin(-rotation), std::cos(rotation), 0.0f);

    // Move spaceship in calculated direction with forward speed
    mesh->position += direction * forwardSpeed;

    // // Wrap around screen edges if necessary
    // wrapAround(mesh->position);
}

// Updates spaceship visual rotation by applying current angle to mesh
void Spaceship::updateRotation() {
    mesh->rotation.z = rotation;    // Set rotation of mesh to current angle
}

// // Wraps spaceship around edges if move out of bounds
// void Spaceship::wrapAround(Vector3 &position) {
//     const float witdh = 42.0f;   // Screen boundary widht
//     const float height = 25.0f;  // Screen boundary height
//
//     // If the spaceship moves beyond the right edge, bring it to the left edge
//     if (position.x > witdh) position.x = -witdh;
//     else if (position.x < -witdh) position.x = witdh;
//
//     // If the spaceship moves beyond the top, bring it to the bottom
//     if (position.y > height) position.y = -height;
//     else if (position.y < -height) position.y = height;
// }
