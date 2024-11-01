#ifndef TRAIL_HPP
#define TRAIL_HPP

#include <threepp/threepp.hpp>
#include <deque>

using namespace threepp;

class Trail {
public:
    // Constructor: sets maximum ponts, small distance between points, and width of segments
    Trail(int maxPoints, float pointSpacing, float trailWidth);

    // Adds a new point to the trail if it's far enough from the last one
    void addPoint(const Vector3& point);

    // Returns list of trail circle meshes to be added for rendering
    const std::deque<std::shared_ptr<Mesh>>& getTrailMeshes() const;

private:
    int maxPoints;                                  // Max number of particle points
    float pointSpacing;                             // Minimum distance between points
    float trailWidth;                               // Diameter of each circle
    std::deque<std::shared_ptr<Mesh>> trailPoints;  // List of meshes forming trail
    Vector3 lastPoint;                              // Last point for checking distance

    // Creates a small circle mesh at specified position, used to represent trail segment
    std::shared_ptr<Mesh> createTrailCircle(const Vector3& position);
};



#endif //TRAIL_HPP
