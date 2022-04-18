/* Jocelyn Dzuong - Project 3
GUI implementation using SFML and ImGui libraries*/

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(900,900), "Shopping Bot");
    char userinput[255] = "Type here";
    ImGui::SFML::Init(window);
    float ImGuiWidth, ImGuiHeight;
    ImGuiWidth = 800;
    ImGuiHeight = 800;
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::SetWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHeight));
        ImGui::Begin("Find the best deals and prices here!");
        ImGui::Text("Search");
        ImGui::InputText("Term", userinput, 255);
        int minRating; 
        int maxRating;
        ImGui::Text("Minimum Rating\n");
        ImGui::SliderInt("Min", &minRating, 0,5);
        ImGui::Text("Maximum Rating\n");
        ImGui::SliderInt("Max", &maxRating, 0,5);
        bool showShirts, showPants, showShoes, showAll;

        ImGui::NewLine();
        ImGui::Text("Item Filters");
        ImGui::Checkbox("Shirts", &showShirts);
        ImGui::SameLine();
        ImGui::Checkbox("Pants", &showPants);
        ImGui::SameLine();
        ImGui::Checkbox("Shoes", &showShoes);
        ImGui::SameLine();
        ImGui::Checkbox("Show all", &showAll);
        //ImGui::SliderFloat("Radius", &circleRadius, 100.0f, 300.0f);
        const float my_values[] = { 4,2,3,4,2 };
        ImGui::PlotLines("Price Change Test\n", my_values, IM_ARRAYSIZE(my_values));
        if (ImGui::Button("Search"))
        {
            // do stuff
        }
        ImGui::End();
        //shape.setRadius(circleRadius);
        window.clear(sf::Color(18,33,43));

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}