#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "CMake SFML Project");
    window.setFramerateLimit(144);
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello, world!");
        ImGui::Button("Look at this pretty button");
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);

        window.display();
    }
    ImGui::SFML::Shutdown();
}
