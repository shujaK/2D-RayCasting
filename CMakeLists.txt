cmake_minimum_required(VERSION 3.28)
project(2D-RayCast LANGUAGES CXX)

include(FetchContent)

# Set policy to handle download timestamps
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SFML_VERSION 2.6.1)
# Using docking branch from git instead of versioned release
# set(IMGUI_SFML_VERSION 2.3)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG        v1.90.4-docking
  # Released version with docking support
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Or by tag...
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
  GIT_TAG        2.6.x
  # GIT_COMMIT 5f54b69b6aee18db846c81633f86f78c2586dded
  # ^ or like this - sometimes it's better because FetchContent won't look
  # into remote to see if branch head was updated or not - good for stable
  # tags like 'vX.X' corresponding to releases
)

## finally, let's build

# SFML
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(imgui-sfml)

add_executable(main 
    src/main.cpp
    src/Wall.cpp
    src/Ray.cpp
    src/Eye.cpp
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main 
    PRIVATE 
        sfml-graphics
        ImGui-SFML::ImGui-SFML
)
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
endif()
