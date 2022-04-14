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
    	string name;
        double shirtPrice;
        double pantsPrice;
        double shoesPrice;
	    double rating;
	    double priceOverTime;
        Website* next;
		Website()
		{
			next = nullptr;
		}
	};

    Website* headPointer;
    Website* tailPointer;
    int numOfWebsites;
    int totalWebsites;
    double minRating;
    bool shirt, pants, shoes;

    void Filter(double minRating, double totalWebsites, bool shirt, bool pants, bool shoes);
    void AddWebsite(string name, double shirtPrice, double pantsPrice, double shoesPrice, double rating, double priceOverTime);
	
};

void AllWebsites::Filter(double minRating, double totalWebsites, bool shirt, bool pants, bool shoes)
{
    this->minRating = minRating;
    this->totalWebsites = totalWebsites;
    this->shirt = shirt;
    this->pants = pants;
    this->shoes = shoes;
    numOfWebsites = 0;
    headPointer = nullptr;
    tailPointer = nullptr;
}

void AllWebsites::AddWebsite(string name, double shirtPrice, double pantsPrice, double shoesPrice, double rating, double priceOverTime)
{
    if(minRating <= rating) {
        Website* newWebsite = new Website();
        newWebsite->name = name;
        newWebsite->shirtPrice = shirtPrice;
        newWebsite->pantsPrice = pantsPrice;
        newWebsite->shoesPrice = shoesPrice;
        newWebsite->rating = rating;
        newWebsite->priceOverTime = priceOverTime;
        if(numOfWebsites == 0) {
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


int main()
{

    return 0;
}