#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = new node;
	head -> img = new Image(3, 4);
    head -> next = NULL;
    listLength = 0;
}

// Setter adds a node to the list at a given position.
// Takes a node and list position as parameters.
// Position must be between 1 and the number of data nodes.
// Returns true if the operation is successful.
bool LinkedList::insertNode( node * newNode, int position )
{
    cout << "\nEntering insertNode ..." << endl;
    if ( (position <= 0) || (position > listLength + 1) )
    {
        cout << "Error: the given position is out of range." << endl;
        return false;
    }
    if (!head -> next)
    {
        head -> next = newNode;
        listLength++;
        return true;
    }
    int count = 0;
    node * p = head;
    node * q = head;
    while (q)
    {
        if (count == position)
        {
            p -> next = newNode;
            newNode -> next = q;
            listLength++;
            return true;
        }
        p = q;
        q = p -> next;
        count++;
    }
    if (count == position)
    {
        p -> next = newNode;
        newNode -> next = q;
        listLength++;
        return true;
    }
    return false;
}

// Setter removes a node by its given position.
// Returns true if the operation is successful.
bool LinkedList::removeNode( int position )
{
    cout << "\nEntering removeNode..." << endl;
    if ( (position <= 0) || (position > listLength + 1) )
    {
        cout << "Error: the given position is out of range." << endl;
        return false;
    }
    if (!head -> next)
    {
        cout << "Error: there is nothing to remove." << endl;
        return false;
    }
    
    int count = 0;
    node * p = head;
    node * q = head;
    while (q)
    {
        if (count == position)
        {
            p -> next = q -> next;
            delete q;
            listLength--;
            cout << "Success: node at position " << position << " was deleted." << endl;
            cout << "listLength = " << listLength << endl;
            return true;
        }
        p = q;
        q = p -> next;
        count++;
    }
    cout << "Error: nothing was removed from the list." << endl;
    return false;
}

// Prints each node in the list in consecutive order,
// starting at the head and ending at the tail.
// Prints list data to the console.
void LinkedList::printListLength()
{
	std::cout << listLength << std::endl;
}

// Destructor de-allocates memory used by the list.
LinkedList::~LinkedList()
{
    node * p = head;
    node * q = head;
    while (q)
    {
        p = q;
        q = p -> next;
        delete p;
    }
}
