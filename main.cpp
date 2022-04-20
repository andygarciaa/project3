/* Jocelyn Dzuong - Project 3
GUI implementation using SFML and ImGui libraries
*/

// Turn off debug dependencies when importing Python modules 
#ifdef _DEBUG
#undef _DEBUG#include <Python.h>

#define _DEBUG
#else#include <Python.h>

#endif

// Include ImGui headers 
#include "imgui.h"

#include "imgui-SFML.h"

#include "imstb_textedit.h"

#include "imstb_truetype.h"

#include "imgui_stdlib.h"

// Include SFML headers
#include <SFML/Graphics/CircleShape.hpp>

#include <SFML/Graphics.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/System/Clock.hpp>

#include <SFML/Window/Event.hpp>

// Include pybind11 headers to integrate Python with C++
#include <pybind11/pybind11.h>

#include <pybind11/embed.h>

// Other necessary STL headers 
#include <string.h>

#include <stdlib.h>

#include <stdio.h>

#include <iostream>

#include <fstream> //This allows for the functions that read into the CSV file

// Header files from Mark
#include "minheap.h"

#include "project3.h"

using namespace std;

// Alias py for calling functions from pybind11
namespace py = pybind11;

//Function that reads data from the CSV File
void GetDataFromCSVFile(string filePath, AllWebsites* theList)
{
    ifstream inFile(filePath);

    if (inFile.is_open())
    {
        // 0. Read the heading data from the file
        string lineFromFile;
        getline(inFile, lineFromFile);

        // Get all entries/records from the file, one line at a time
        while (getline(inFile, lineFromFile))
        {
            // Create a stream from the line of data from the file
            istringstream stream(lineFromFile);

            string itemName;
            string tempPrice;
            double price;
            string tempRating;
            double rating;
            string theURL;

            getline(stream, itemName, ',');
            getline(stream, tempPrice, ',');
            price = stod(tempPrice);
            getline(stream, tempRating, ',');
            rating = stod(tempRating);
            getline(stream, theURL);

            theList.AddWebsite(itemName, price, rating, theURL);
        }
    }
}
void CreateShirtHeap(WebNode* minHeap, AllWebsites* theList)
{
    AllWebsites* placeHolder = theList;
    while(placeHolder->headPointer != NULL) {
        WebNode newNode;
        newNode.CreateNode(placeHolder->headPointer->shirtPrice, placeHolder->headPointer->name, "Shirt");
        placeHolder->headPointer = placeHolder->headPointer->next;
    }
    minHeap.heapify(minHeap, minHeap.size(), 0);
}

void CreatePantsHeap(WebNode* minHeap, AllWebsites* theList)
{
    AllWebsites* placeHolder = theList;
    while(placeHolder->headPointer != NULL) {
        WebNode newNode;
        newNode.CreateNode(placeHolder->headPointer->pantsPrice, placeHolder->headPointer->name, "Pants");
        placeHolder->headPointer = placeHolder->headPointer->next;
    }
    minHeap.heapify(minHeap, minHeap.size(), 0);
}


void CreateShoesHeap(WebNode* minHeap, AllWebsites* theList)
{
    AllWebsites* placeHolder = theList;
    while(placeHolder->headPointer != NULL) {
        WebNode newNode;
        newNode.CreateNode(placeHolder->headPointer->shoesPrice, placeHolder->headPointer->name, "Shoes");
        placeHolder->headPointer = placeHolder->headPointer->next;
    }
    minHeap.heapify(minHeap, minHeap.size(), 0);
}

// Driver function handling window event of ImGui-SFML
int main() {
    AllWebsites theList;
    //theList.Filter(minRating, shirt, pants, shoes); this will be dependent on the user input from the GUI but it HAS to be called before collecting the data
    //GetDataFromCSVFile("Name of file Here", theList);
    /*=== Now create the minheap from the linked list ===*/
    /*
    if(theList->shirt == true) {
        WebNode shirtHeap[theList->numOfWebsites];
        CreateShirtHeap(shirtHeap);
    }
    if(theList->pants == true) {
        WebNode pantsHeap[theList->numOfWebsites];
        CreatePantsHeap(pantsHeap);
    }
    if(theList->shoes == true) {
        WebNode shoesHeap[theList->numOfWebsites];
        CreateShoesHeap(shoesHeap);
    }
    */
    // Declare a Python interpreter to use in program
    py::scoped_interpreter guard{};

    // Import custom Python file with defined functions in solution directory
    // Will only accept custom  module names without .py extension!!! 
    // Otherwise an error will be pulled
    py::module testermod = py::module::import("hehehe");

    // Start the active window in ImGui + SFML with size and title of window 
    sf::RenderWindow window(sf::VideoMode(900, 900), "Shopping Bot");
    ImGui::SFML::Init(window);

    // Variables for text input, ImGui size dimenions, window clocks, and if buttons were clicked
    char userinput[255] = "Type here"; // Cannot be declared empty unfortunately
    float ImGuiWidth, ImGuiHeight;
    ImGuiWidth = 800;
    ImGuiHeight = 800;
    sf::Clock deltaClock;
    static bool searchClicked = false;
    static bool minHeapClicked = false;
    static bool linkedListClicked = false;

    // Variables for ratings, checkbox filters, and array of floats for graph 
    int minRating;
    int maxRating;
    bool showShirts, showPants, showShoes, showAll;
    const float my_values[] = {
      4,
      2,
      3,
      4,
      2
    };

    while (window.isOpen()) {
        // Creates object for active window event and using deltaClock for upkeep of ImGui instance
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        // Sets ImGui window size
        ImGui::SetWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHeight));

        // ImGui window title, search input, and sliders for minimum and maximum rating
        ImGui::Begin("Find the best deals and prices here!");
        ImGui::Text("Search");
        ImGui::InputText("Term", userinput, 255);
        ImGui::Text("Minimum Rating\n");
        ImGui::SliderInt("Min", &minRating, 0, 5);
        ImGui::Text("Maximum Rating\n");
        ImGui::SliderInt("Max", &maxRating, 0, 5);

        // Checkbox filters for types of clothing to look up 
        ImGui::NewLine();
        ImGui::Text("Item Filters");
        ImGui::Checkbox("Shirts", &showShirts);
        ImGui::SameLine();
        ImGui::Checkbox("Pants", &showPants);
        ImGui::SameLine();
        ImGui::Checkbox("Shoes", &showShoes);
        ImGui::SameLine();
        ImGui::Checkbox("Show all", &showAll);

        // Graph for testing, parses array of floats. Here by default but subject to change 
        ImGui::PlotLines("Price Change Test\n", my_values, IM_ARRAYSIZE(my_values));

        // If search button is clicked, sets bool to true and runs python function
        if (ImGui::Button("Search")) {
            searchClicked = true;
        }
        // End of first ImGui instance with search UI
        ImGui::End();

        /*
        Runs when search button is clicked
        Calls a function from custom Python file, casts it into appropriate variable type, and prints results
        on a new window in ImGui
        All ImGui window instances must always begin with ImGui::Begin(string title) and end with ImGui::End()!!!
        */
        if (searchClicked) {

            // attr(string) accepts any defined function from Python file along with paramaters 
            py::object result = testermod.attr("add")(25, 4);
            int test = (result.cast < int >());

            // Begins a new popup window with results
            ImGui::SetWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHeight));
            ImGui::Begin("Results");
            ImGui::Text("You called the add function in Python! add(25,4) is ");
            ImGui::Text("%d", test);

            // Two buttons to show results in min heap and linked list 
            // windows handled after ImGui::End() of this current results window 
            if (ImGui::Button("Show in Min Heap")) {
                minHeapClicked = true;
            }
            ImGui::SameLine();
            if (ImGui::Button("Show in Linked List")) {
                linkedListClicked = true;
            }
            ImGui::End();
        }
        // Tests Linked List implementation
        if (linkedListClicked) {
            ImGui::SetWindowSize(ImVec2((float)ImGuiWidth * 7, (float)ImGuiHeight * 7));
            ImGui::Begin("Linked List");
            AllWebsites testCollectionOfWebsites;
            testCollectionOfWebsites.Filter(1, 3, true, true, true);
            testCollectionOfWebsites.AddWebsite("Adidas", 2.00, 5.00, 3.00, 1, 2);
            testCollectionOfWebsites.AddWebsite("Amazon", 1, 3, 3, 1, 5);
            testCollectionOfWebsites.AddWebsite("Shein", 4, 7, 4, 1, 1);

            string llresults = testCollectionOfWebsites.printAllWebsitesLinkedList(&testCollectionOfWebsites);
            const char* convertresults = llresults.c_str();
            ImGui::Text(convertresults);
            //ImGui::Text("");
            ImGui::End();
        }
        if (minHeapClicked) {
            ImGui::SetWindowSize(ImVec2((float)ImGuiWidth * 7, (float)ImGuiHeight * 7));
            ImGui::Begin("Min Heap");
            WebNode collectionOfWebsites[2];
            WebNode nodeOne;
            WebNode nodeTwo;
            nodeOne.CreateNode(2, "Adidas", "sneakers");
            nodeTwo.CreateNode(3, "Amazon", "shorts");
            collectionOfWebsites[0] = nodeOne;
            collectionOfWebsites[1] = nodeTwo;
            heapify(collectionOfWebsites, 2, 0);
            string minimumPrice = to_string(returnMin(collectionOfWebsites).getPrice());
            ImGui::Text("You added Adidas sneakers worth $2 and Amazon shorts worth $3");
            ImGui::NewLine();
            ImGui::Text("The minimum price using minheap is ");
            const char* convertMinPrice = minimumPrice.c_str();
            ImGui::Text(convertMinPrice);
            ImGui::End();

        }
        // Sets background color using SFML
        window.clear(sf::Color(18, 33, 43));

        // Draws ImGui::SFML window in a loop by frames and displays each time
        ImGui::SFML::Render(window);
        window.display();
    }

    // Shuts down when close button is clicked on top to clear ImGui-SFML instances 
    ImGui::SFML::Shutdown();
    return 0;
}
