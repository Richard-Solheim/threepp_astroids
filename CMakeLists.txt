cmake_minimum_required(VERSION 3.19)
project(astroids)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 2e2397e0b7f0e639f254ea3046b70e53a71f0387
)
FetchContent_MakeAvailable(threepp)

add_subdirectory(external)

add_executable(astroids main.cpp
        Spaceship.cpp
        Spaceship.hpp
        Trail.cpp
        Trail.hpp
        Stars.cpp
        Stars.hpp
        Asteroid.cpp
        Asteroid.hpp
        Asteroids.cpp
        Asteroids.hpp
)
target_link_libraries(astroids PRIVATE threepp::threepp imgui::imgui)
