#include "Stars.hpp"
#include "random"

using namespace threepp;

// Constructor: Initializes star field with specified number stars and spread range

Stars::Stars(int numStars, float spread) {
    // Create a group to hold all star meshes
    starsGroup = Group::create();

    // Generate each star and add to group
    for (int i = 0; i < numStars; i++) {
        starsGroup->add(createStar(spread));    // Create a star and add to group
    }
}

// Returns group containing star, allowing to add to scene
std::shared_ptr<Group> Stars::getStarsGroup() const {
    return starsGroup;
}

// Create a single star mesh with a small sphere with a random position
std::shared_ptr<Mesh> Stars::createStar(float spread) {
    // Create small sphere geometry for stars
    auto geometry = SphereGeometry::create(0.1f, 8, 8); // Small radius for low detail

    // Basic white material to represent stars
    auto material = MeshBasicMaterial::create();
    material->color = Color::white;

    // Create a mesh with geometry and material
    auto star = Mesh::create(geometry, material);

    // Use random numbers to randomly place stars inside the spread range
    // Random number generator for x, y and z coordinate
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(-spread, spread);

    // Randomly assign position withing spread range
    star->position.set(distrib(gen), distrib(gen), distrib(gen));

    return star;
}

