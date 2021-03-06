//Mark Herring
//Group project
//linked list implementation
#include <iomanip>
#include <iostream>
#include <fstream> // Acces to of-, if-, fstream
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class AllWebsites
{
    struct Website {
    public:
        string itemName;
        double price;
        double rating;
        string theURL;
        Website* next;
        Website()
        {
            next = nullptr;
        }
    };
public:
    Website* headPointer;
    Website* tailPointer;
    int numOfWebsites;
    double minRating;
    bool shirt, pants, shoes;

    void Filter(double minRating, bool shirt, bool pants, bool shoes);
    void AddWebsite(string itemName, double price, double rating, string theURL);
    string printAllWebsitesLinkedList(AllWebsites* p);

};

void AllWebsites::Filter(double minRating, bool shirt, bool pants, bool shoes)
{
    this->minRating = minRating;
    this->shirt = shirt;
    this->pants = pants;
    this->shoes = shoes;
    numOfWebsites = 0;
    headPointer = nullptr;
    tailPointer = nullptr;
}

void AllWebsites::AddWebsite(string itemName, double price, double rating, string theURL)
{

    if (minRating <= rating) {
        Website* newWebsite = new Website();

        newWebsite->itemName = itemName;
        newWebsite->price = price;
        newWebsite->rating = rating;
        newWebsite->theURL = theURL;
        if (numOfWebsites == 0) {
            headPointer = newWebsite;
            tailPointer = newWebsite;
        }
        else {
            tailPointer->next = newWebsite;
            tailPointer = newWebsite;
        }
        numOfWebsites++;
    }
}

string AllWebsites::printAllWebsitesLinkedList(AllWebsites* p) {
    AllWebsites* curr = p;
    string results = "";
    if (curr->numOfWebsites == 0) {
        return "Linked List is empty!";
    }


    while (curr->headPointer != NULL) {

        string sh = to_string(curr->headPointer->shirtPrice);
        string pa = to_string(curr->headPointer->pantsPrice);
        string se = to_string(curr->headPointer->shoesPrice);
        string rt = to_string(curr->headPointer->rating);


        results += "Product name: " + curr->headPointer->name + ", ";
        results += "Shirt price: " + sh.substr(0, sh.length() - 4) + ", ";
        results += "Pants price: " + pa.substr(0, pa.length() - 4) + ", ";
        results += "Pants price: " + se.substr(0, se.length() - 4) + ", ";
        results += "Rating: " + rt.substr(0, rt.length() - 4) + " -> " + "\n";
        curr->headPointer = curr->headPointer->next;
    }

    return results;

}
