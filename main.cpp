#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "spaceship.hpp"

using namespace threepp;

int main() {
    Canvas canvas;
    GLRenderer renderer{canvas.size()};

    // Create a perspective camera and set an initial position
    PerspectiveCamera camera(60, canvas.aspect(), 0.1, 1000);
    camera.position.z = 40; // Initial distance from spaceship

    Scene scene;
    scene.background = Color::black;

    // Create spaceship mesh and add to scene
    auto spaceship = std::make_shared<Spaceship>();
    scene.add(spaceship->getMesh());

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

        // Render scene
        renderer.render(scene, camera);
    });

}