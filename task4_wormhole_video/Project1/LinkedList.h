
#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
using namespace std;

//***********************************************************************************
// Node structs contain data and a pointer to the next node.
// In this project, it will represent a song/artist combination.
//***********************************************************************************
struct node
{
	cv::Mat * img;
    node * next;
};

//***********************************************************************************
// LinkedList is a list of singly-linked nodes.
// In this project, it will represent a song playlist.
//***********************************************************************************
class LinkedList
{
private:
    // Head of the list contains no song data, but points to the song playlist.
    node * head;
	node * current;
    int listLength;
    
public:
    // Default Constructor creates the head node.
    LinkedList();
    
    // Setter adds a node to the list at a given position.
    // Takes a node and list position as parameters.
    // Position must be between 1 and the number of data nodes.
    // Returns true if the operation is successful.
    bool insertNode( node * newNode, int position );
    
    // Setter removes a node by its given position.
    // Returns true if the operation is successful.
    bool removeNode( int position );

	bool push_back(cv::Mat img);

	node * next();

    // Prints each node in the list in consecutive order,
    // starting at the head and ending at the tail.
    // Prints list data to the console.
    void printListLength();

	int size();
	cv::Mat getCurrentImage();
	
    // Destructor de-allocates memory used by the list.
    ~LinkedList();
};

#endif
