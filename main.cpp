#include "threepp/extras/imgui/ImguiContext.hpp"
#include "threepp/threepp.hpp"

#include "threepp/canvas/Monitor.hpp"

#include <set>
#include <cmath>
#include <sstream>

#include "Asteroids.hpp"
#include "Bullet.hpp"
#include "CollisionHandler.hpp"
#include "Spaceship.hpp"
#include "Stars.hpp"
#include "Trail.hpp"
#include "cmake-build-debug/_deps/threepp-src/src/external/nlohmann/nlohmann/json.hpp"

using namespace threepp;

int main() {
    // Set up the rendering canvas and renderer
    Canvas canvas("Astroids game");
    int height = monitor::monitorSize().height() / 2;
    int width = monitor::monitorSize().width() / 2;
    canvas.setSize({width, height});
    GLRenderer renderer{canvas.size()};
    renderer.autoClear = false;

    // Definiteions to change the game
    float playArea = 100.0f;          // Defining play area
    float starNumber = 1000;            // Defining amount of stars
    float maxAsteroids = 50;            // Defining max number asteroids

    float cameraWidth = 30;
    float cameraHeight = 20;
    auto camera = OrthographicCamera::create(-cameraWidth, cameraWidth, cameraHeight, -cameraHeight, 0.1f, 1000.0f);
    camera->position.z = 500;  // Adjust as needed to see the entire scene

    // Set up the scene with black background
    Scene scene;
    scene.background = Color::black;

    // Create a scoreboard at the top of the screen
    HUD hud(canvas.size());
    FontLoader fontLoader;
    const std::optional<Font> font = fontLoader.defaultFont();
    TextGeometry::Options opts((font.value()), 20, 5);    // Font, size and thickness

    // Creating the text
    int score = 0;
    std::stringstream scoreText;
    scoreText << "Score: " << score;

    auto scoreDisplay = Text2D(opts, scoreText.str());
    scoreDisplay.setColor(Color::white);

    // Adding text to the hud
    hud.add(scoreDisplay, HUD::Options()
        .setNormalizedPosition(Vector2(0.5f, 0.95f))    // Position in the top center
        .setVerticalAlignment(HUD::VerticalAlignment::TOP)
        .setHorizontalAlignment(HUD::HorizontalAlignment::CENTER));

    canvas.onWindowResize([&](WindowSize size) {
        renderer.setSize(size);
        hud.setSize(size);
    });

    // Create spaceship mesh with boundary limits and add to scene
    auto spaceship = std::make_shared<Spaceship>(playArea, playArea);
    scene.add(spaceship->getMesh());

    // Create trail effect for the spaceship and add to scene
    auto trail = std::make_shared<Trail>(25, 0.5f, 0.8f);  // Max 25 points, 0.5 distance between, 0.8 width

    // Container for bullets
    std::vector<std::shared_ptr<Bullet>> bullets;

    // Create a star field with stars spread over range of the play area
    auto stars = std::make_shared<Stars>(starNumber, playArea);
    scene.add(stars->getStarsGroup());  // Add the star group to the scene

    // Create asteroid manager
    float spawnRange = 75.0f;
    auto asteroids = std::make_shared<Asteroids>(maxAsteroids, spawnRange);

    for (const auto& asteroidMesh : asteroids->getAsteroidMeshes()) {
        scene.add(asteroidMesh);
    }

    // Create collision handler
    CollisionHandler collisionHandler(2.0f);    // Adjust after need

    // Variables to track movement states based on user input
    bool rotateLeft = false;
    bool rotateRight = false;
    bool moveForward = false;
    bool fireBullet = false;

    // Controls for spaceship
    auto keyPressedListener = std::make_shared<KeyAdapter>(KeyAdapter::Mode::KEY_PRESSED, [&](KeyEvent event) {
        if (event.key == Key::A) rotateLeft = true;
        if (event.key == Key::D) rotateRight = true;
        if (event.key == Key::W) moveForward = true;
        if (event.key == Key::SPACE) fireBullet = true;
    });

    auto keyReleasedListener = std::make_shared<KeyAdapter>(KeyAdapter::Mode::KEY_RELEASED, [&](KeyEvent event) {
       if (event.key == Key::A) rotateLeft = false;
       if (event.key == Key::D) rotateRight = false;
       if (event.key == Key::W) moveForward = false;
       if (event.key == Key::SPACE) fireBullet = false;
    });

    // Adding key listeners to canvas to capture user input
    canvas.addKeyListener(*keyPressedListener);
    canvas.addKeyListener(*keyReleasedListener);

    Clock clock;

    // Animation loop
    canvas.animate([&]() {
        // Control movement based off keys pressed
        if (rotateLeft)  spaceship->rotateLeft();
        if (rotateRight) spaceship->rotateRight();
        if (moveForward) spaceship->moveForward();

        // Update camera position to follow spaceship
        Vector3 spaceshipPosition = spaceship->getMesh()->position;
        camera->position.x = spaceshipPosition.x;
        camera->position.y = spaceshipPosition.y;
        camera->position.z = spaceshipPosition.z + 40;

        spaceship->update();

        // Ensure camera looks at spaceship
        camera->lookAt(spaceshipPosition);

        // Add current spaceship position to trail
        trail->addPoint(spaceshipPosition);

        // Set to store meshes that have been added to scene
        std::set<std::shared_ptr<Mesh>> addedTrailMeshes;
        std::set<std::shared_ptr<Mesh>> addedAsteroidMeshes;

        // Add each part of trail to scene if not already present
        for (const auto& trailMesh : trail->getTrailMeshes()) {
            if (addedTrailMeshes.find(trailMesh) == addedTrailMeshes.end()) {
                scene.add(trailMesh);
                addedTrailMeshes.insert(trailMesh);
            }
        }

        // Update existing bullets
        for (auto it = bullets.begin(); it != bullets.end();) {
            auto& bullet = *it;
            bullet->update();

            // Remove when out of bounds
            if (bullet->isOutOfBounds(playArea, playArea)) {
                scene.remove(*bullet->getMesh());
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }

        // Fire a new bullet when SPACE is pressed
        if (fireBullet) {
            // Access rotation of spaceship mesh
            float rotationZ = spaceship->getMesh()->rotation.z;     // Get Z-axis rotation

            // Calculate direction vector from ship rotation
            Vector3 direction(-std::sin(rotationZ), std::cos(rotationZ), 0);

            // Create and fire bullet
            auto bullet = std::make_shared<Bullet>(spaceship->getMesh()->position, direction);
            bullets.push_back(bullet);
            scene.add(bullet->getMesh());
            fireBullet = false;                 // Prevent endless firing
        }

        // Update asteroids, remove out of bounds and respawn
        asteroids->update(spaceship->getMesh()->position);
        for (const auto& asteroidMesh : asteroids->getAsteroidMeshes()) {
            if (addedAsteroidMeshes.find(asteroidMesh) == addedAsteroidMeshes.end()) {
                scene.add(asteroidMesh);
                addedAsteroidMeshes.insert(asteroidMesh);
            }
        }

        // Check for collision between ship and asteroid
        if (collisionHandler.checkCollision(spaceship->getMesh(), asteroids->getAsteroidMeshes())) {
            CollisionHandler::handleShipCollision(spaceship->getMesh(), *asteroids, scene);
        }

        // Check for collision between bullet and asteroid
        collisionHandler.bulletAsteroidCollision(bullets, *asteroids, scene, score);

        // Update HUD to reflect score
        scoreText.str("");
        scoreText << "Score: " << score;
        scoreDisplay.setText(scoreText.str());

        // Render scene
        renderer.clear();
        renderer.render(scene, *camera);
        hud.apply(renderer);
    });

}