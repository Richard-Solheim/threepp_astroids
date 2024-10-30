#include "Trail.hpp"

#include <complex>

using namespace threepp;

Trail::Trail(int maxPoints, float pointSpacing, float trailWidth)
               : maxPoints(maxPoints), pointSpacing(pointSpacing), trailWidth(trailWidth) {

}

// Adds new point to trail, as circle, if far enough from previous point
void Trail::addPoint(const Vector3& point) {
    // Only add new trail point if far enough from last point
    if (trailPoints.empty() || (point.distanceTo(lastPoint) >= pointSpacing)) {
        // Creates new circle mesh at this position and add to trail
        trailPoints.push_back(createTrailCircle(point));
        lastPoint = point;      // Update last point to the new one

        // Remove the oldest point if max is reached
        if (trailPoints.size() > maxPoints) {
            trailPoints.pop_back(); // Efficient removal from back
        }
    }
}

// Creates a small circle mesh to represent a trail segment at a specified position
std::shared_ptr<Mesh> Trail::createTrailCircle(const Vector3& position) {
    // Create a circle geometry
    auto geometry = BufferGeometry::create();

    // Generate vertices for a circular shape to use for each trail segment
    std::vector<float> vertices;
    int sides = 25;
    float radius = trailWidth / 2.0f;
    for (int i = 0; i < sides; i++) {
        float theta = (i * 2.0f * M_PI) / sides;    // Calculate angle for each vertex
        vertices.push_back(radius * std::cos(theta));   // x coordinates
        vertices.push_back(radius * std::sin(theta));   // y coordinates
        vertices.push_back(0.0f);                       // z coordinates (flat on XY plane)
    }
    geometry->setAttribute("position", FloatBufferAttribute::create(vertices, 3));

    // Create a material for the trail segment (circle)
    auto material = MeshBasicMaterial::create();
    material->color = Color::white;
    material->side = Side::Double;          // Makes it visible from both sides

    // Create the circle mesh and set its position
    auto circle = Mesh::create(geometry, material);
    circle->position = position;

    return circle;
}

// Returns the list of all trail circle meshes, to be added to the scene for rendering
const std::deque<std::shared_ptr<Mesh>>& Trail::getTrailMeshes() const {
    return trailPoints;
}