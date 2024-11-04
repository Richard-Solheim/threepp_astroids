#include "Bullet.hpp"

// Constructor: Initializes bullet with position and direction
Bullet::Bullet(const Vector3& position, const Vector3& direction)
    : speed(0.5f), direction(direction) {
    // Create mesh to represent bullet
    auto geometry = SphereGeometry::create(0.2f, 8, 8);
    auto material = MeshBasicMaterial::create();
    material->color = Color::yellow;
    mesh = Mesh::create(geometry, material);

    // Set initial position of the bullet
    mesh->position = position;
}

// Updates the bullets position
void Bullet::update() {
    mesh->position += direction * speed;    // Move bullet in its direction by its speed
}

// Checks if bullet is out of bounds
bool Bullet::isOutOfBounds(float boundaryX, float boundaryY) const {
    return std::abs(mesh->position.x) > boundaryX || std::abs(mesh->position.y) > boundaryY;
}

// Access bullet mesh
std::shared_ptr<Mesh> Bullet::getMesh() const {
    return mesh;
}


