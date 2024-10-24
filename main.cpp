#include <iostream>
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/ImguiContext.hpp"

#include "Spaceship.hpp"

namespace {

    auto createMesh() {
        const auto geometry = BoxGeometry::create();
        const auto material = MeshBasicMaterial::create();
        material->color = Color::darkred;

        auto mesh = Mesh::create(geometry, material);

        return mesh;
    }

}

int main() {

    Canvas canvas;
    GLRenderer renderer{canvas.size()};

    PerspectiveCamera camera(60, canvas.aspect(), 0.1, 1000);
    camera.position.z = 5;

    Scene scene;
    scene.background = Color::black;

    auto mesh = createMesh();
    scene.add(mesh);

    bool& meshVisible = mesh->visible;

    ImguiFunctionalContext ui(canvas.windowPtr(), [&meshVisible] {
        ImGui::SetNextWindowPos({}, 0, {});
               ImGui::SetNextWindowSize({230, 0}, 0);
               ImGui::Begin("Mesh settings");
               ImGui::Checkbox("Visible", &meshVisible);

               ImGui::End();
    });

    canvas.animate([&] {
        renderer.render(scene, camera);
        ui.render();
    });
}