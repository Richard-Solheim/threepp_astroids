#include "Stars.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

#include <set>

#include "spaceship.hpp"
#include "Trail.hpp"

using namespace threepp;

int main() {
    // Set up the rendering canvas and renderer
    Canvas canvas;
    GLRenderer renderer{canvas.size()};

    // Create a perspective camera and set an initial position
    PerspectiveCamera camera(60, canvas.aspect(), 0.1, 1000);
    camera.position.z = 40; // Initial distance from spaceship

    // Set up the scene with black background
    Scene scene;
    scene.background = Color::black;

    // Define play area
    float playArea = 100.0f;

    // Create spaceship mesh with boundary limits and add to scene
    auto spaceship = std::make_shared<Spaceship>(playArea, playArea);
    scene.add(spaceship->getMesh());

    // Create trail effect for the spaceship and add to scene
    auto trail = std::make_shared<Trail>(25, 0.5f, 0.8f);  // Max 100 points, 0.5 distance between, 0.3 width

    // Create a star field with 400 stars spread over range of the play area
    auto stars = std::make_shared<Stars>(400, playArea);
    scene.add(stars->getStarsGroup());  // Add the star group to the scene

    // Variables to track movement states based on user input
    bool rotateLeft = false;
    bool rotateRight = false;
    bool moveForward = false;

    // Controls for spaceship
    auto keyPressedListener = std::make_shared<KeyAdapter>(KeyAdapter::Mode::KEY_PRESSED, [&](KeyEvent event) {
        if (event.key == Key::A) rotateLeft = true;
        if (event.key == Key::D) rotateRight = true;
        if (event.key == Key::W) moveForward = true;
    });

    auto keyReleasedListener = std::make_shared<KeyAdapter>(KeyAdapter::Mode::KEY_RELEASED, [&](KeyEvent event) {
       if (event.key == Key::A) rotateLeft = false;
       if (event.key == Key::D) rotateRight = false;
       if (event.key == Key::W) moveForward = false;
    });

    // Adding key listeners to canvas to capture user input
    canvas.addKeyListener(*keyPressedListener);
    canvas.addKeyListener(*keyReleasedListener);

    // Animation loop
    canvas.animate([&] {
        // Control movement based off keys pressed
        if (rotateLeft)  spaceship->rotateLeft();
        if (rotateRight) spaceship->rotateRight();
        if (moveForward) spaceship->moveForward();

        // Update camera position to follow spaceship
        Vector3 spaceshipPosition = spaceship->getMesh()->position;
        camera.position.x = spaceshipPosition.x;
        camera.position.y = spaceshipPosition.y;
        camera.position.z = spaceshipPosition.z + 40;

        // Ensure camera looks at spaceship
        camera.lookAt(spaceshipPosition);

        // Add current spaceship position to trail
        trail->addPoint(spaceshipPosition);

        // Set to store meshes that have been added to scene
        std::set<std::shared_ptr<Mesh>> addedTrailMeshes;

        // Add each part of trail to scene if not already present
        for (const auto& trailMesh : trail->getTrailMeshes()) {
            if (addedTrailMeshes.find(trailMesh) == addedTrailMeshes.end()) {
                scene.add(trailMesh);
                addedTrailMeshes.insert(trailMesh);
            }
        }

        // Render scene
        renderer.render(scene, camera);
    });

}