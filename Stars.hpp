#ifndef STARS_HPP
#define STARS_HPP

#include "threepp/threepp.hpp"
#include <vector>

using namespace threepp;

class Stars {
public:
    // Constructor: Initializes star field with specified number stars and spread range
    Stars(int numStars, float spread);

    // Returns group off all stars, so they can be added to the scene
    std::shared_ptr<Group> getStarsGroup() const;

private:
    std::shared_ptr<Group> starsGroup;  // Group containing all star meshes

    // Create a single star mesh with a small sphere with a random position
    std::shared_ptr<Mesh> createStar(float spread);
};



#endif //STARS_HPP
