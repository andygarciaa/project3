//Mark Herring
//Group project
//min heap implementation
#include <iomanip>
#include <iostream>
#include <fstream> // Acces to of-, if-, fstream
#include <vector>
#include <sstream>
#include <string>
using namespace std;

class WebNode
{
private:
    double price;
    string website;
    string item;
public:
    void CreateNode(double price, string website, string item);
    double getPrice();
};

void WebNode::CreateNode(double price, string website, string item)
{  
    this->price = price;
    this->website = website;
    this->item = item;
}

double WebNode::getPrice()
{
    return price;
}

void heapify(WebNode heap[], int size, int index)
{
    int smallest = index;
    int l = 2 * index + 1; 
    int r = 2 * index + 2; 
 
    if (l < size && heap[l].getPrice() < heap[smallest].getPrice()) //The implementation is based off price, what ever is cheapest goes to the root
        smallest = l;
 
    if (r < size && heap[r].getPrice() < heap[smallest].getPrice())
        smallest = r;
 
    if (smallest != index) {
        swap(heap[index], heap[smallest]);

        heapify(heap, size, smallest);
    }
}

WebNode returnMin(WebNode arr[])
{
    return arr[0];
}



int main()
{
    //In the main function is where we will create all of the website nodes storing the data from each website
    //After that we will add each node to our array, so we could have a for loop that each cycle creates a node then adds to the heap array
    int size = 10; //Dependent on the number of websites 
    WebNode heap[size];

    //Method of adding all the nodes to the heap
    //Have a for loop
    //Each cycle will insert the newly created object "Website" at the end of the array,
    //After inserting object at the end of the array, we will call the heapify function in order to put the min value at the root.
    
    //Only other function implemented is return min function which simply returns the object at index 0
    return 0;
}

