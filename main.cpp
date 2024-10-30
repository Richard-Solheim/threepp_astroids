#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"
#include "spaceship.hpp"

using namespace threepp;

int main() {
    Canvas canvas;
    GLRenderer renderer{canvas.size()};

    PerspectiveCamera camera(60, canvas.aspect(), 0.1, 1000);
    camera.position.z = 40;

    Scene scene;
    scene.background = Color::black;

    // Create spaceship mesh
    auto spaceship = std::make_shared<Spaceship>();
    scene.add(spaceship->getMesh());

    bool rotateLeft = false;
    bool rotateRight = false;
    bool moveForward = false;

    auto keyPressedListener = std::make_shared<KeyAdapter>(KeyAdapter::Mode::KEY_PRESSED, [&](KeyEvent event) {
        if (event.key == Key::A) {
            rotateLeft = true;
        }
        if (event.key == Key::D) {
            rotateRight = true;
        }
        if (event.key == Key::W) {
            moveForward = true;
        }
    });

    auto keyReleasedListener = std::make_shared<KeyAdapter>(KeyAdapter::Mode::KEY_RELEASED, [&](KeyEvent event) {
       if (event.key == Key::A) {
           rotateLeft = false;
       }
       if (event.key == Key::D) {
           rotateRight = false;
       }
       if (event.key == Key::W) {
           moveForward = false;
       }
    });

    canvas.addKeyListener(*keyPressedListener);
    canvas.addKeyListener(*keyReleasedListener);

    canvas.animate([&] {
        if (rotateLeft) {
            spaceship->rotateLeft();
        }
        if (rotateRight) {
            spaceship->rotateRight();
        }
        if (moveForward) {
            spaceship->moveForward();
        }

        renderer.render(scene, camera);
    });

}