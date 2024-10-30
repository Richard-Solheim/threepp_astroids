#include "spaceship.hpp"
#include <cmath>

using namespace threepp;

Spaceship::Spaceship() : spaceshipRotation(0.0f), spaceshipRotationSpeed(0.05f), spaceshipForwardSpeed(0.2f) {

    auto geometry = BufferGeometry::create();
    std::vector<float> vertices = {
        0.0f, 1.0f, 0.0f,      // Tip of triangle
        -1.0f, -1.0f, 0.0f,    // Bottom left corner
        1.0f, -1.0f, 0.0f      // Bottom right corner
    };
    geometry->setAttribute("position", FloatBufferAttribute::create(vertices, 3));

    auto material = MeshBasicMaterial::create();
    material->color = Color::darkred;

    spaceshipMesh = Mesh::create(geometry, material);
    spaceshipMesh->position.set(0, 0, 0);
}

std::shared_ptr<Mesh> Spaceship::getMesh() const {
    return spaceshipMesh;
}

void Spaceship::rotateLeft() {
    spaceshipRotation = spaceshipRotation - spaceshipRotationSpeed;
    updateRotation();
}

void Spaceship::rotateRight() {
    spaceshipRotation = spaceshipRotation + spaceshipRotationSpeed;
    updateRotation();
}

void Spaceship::moveForward() { // Fin enklere måte å løse!!!
    Vector3 direction(std::sin(-spaceshipRotation), std::cos(spaceshipRotation), 0.0f);
    spaceshipMesh->position += direction * spaceshipForwardSpeed;
    wrapAround(spaceshipMesh->position);
}

void Spaceship::updateRotation() {
    spaceshipMesh->rotation.z = spaceshipRotation;
}
void Spaceship::wrapAround(Vector3 &position) {
    const float witdh = 42.0f;
    const float height = 25.0f;

    if (position.x > witdh) position.x = -witdh;
    else if (position.x < -witdh) position.x = witdh;

    if (position.y > height) position.y = -height;
    else if (position.y < -height) position.y = height;
}
