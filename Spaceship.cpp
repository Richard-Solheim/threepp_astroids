#include "spaceship.hpp"
#include <cmath>

using namespace threepp;


// Constructor: initializes the spaceship's geometry, color, and initial values
Spaceship::Spaceship(float boundaryX, float boundaryY)
            : rotation(0.0f), rotationSpeed(0.05f), forwardSpeed(0.2f),
              minX(-boundaryX), maxX(boundaryX), minY(-boundaryY), maxY(boundaryY) {

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

    // Calculate new position components
    float newX = mesh->position.x + direction.x * forwardSpeed;
    float newY = mesh->position.y + direction.y * forwardSpeed;

    // Check if each component is at the borders
    if (newX >= minX && newX <= maxX) {
        mesh->position.x = newX;    // Update x position if within bounds
    }
    if (newY >= minY && newY <= maxY) {
        mesh->position.y = newY;
    }

}

// Updates spaceship visual rotation by applying current angle to mesh
void Spaceship::updateRotation() {
    mesh->rotation.z = rotation;    // Set rotation of mesh to current angle
}
