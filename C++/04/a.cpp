#include <iostream>
using namespace std;

// Define the Node structure
struct Node {
    int data;          // Data stored in the node
    Node* next;        // Pointer to the next node

    // Constructor
    Node(int value) : data(value), next(nullptr) {
        cout << "Node " << data << " created." << endl;
    }

    // Destructor
    ~Node() {
        cout << "Node " << data << " deleted." << endl;
    }
};

// Function to create a linked list with 1000 nodes
Node* createLinkedList(int numNodes) {
    Node* head = new Node(1); // Create the head node
    Node* current = head;     // Pointer to traverse the list

    // Create and connect the remaining nodes
    for (int i = 2; i <= numNodes; i++) {
        Node* newNode = new Node(i); // Create a new node
        current->next = newNode;    // Connect the current node to the new node
        current = newNode;          // Move to the new node
    }

    return head; // Return the head of the linked list
}

int main() {
    int numNodes = 1000; // Number of nodes to create

    // Create the linked list
    Node* head = createLinkedList(numNodes);

    // Print the linked list
    Node* temp = head; // Temporary pointer to traverse the list
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next; // Move to the next node
    }
    cout << "nullptr" << endl;

    // Free allocated memory
    temp = head; // Reset temp to the head
    while (temp != nullptr) {
        Node* nextNode = temp->next; // Store the next node
        delete temp;                 // Delete the current node
        temp = nextNode;             // Move to the next node
    }

    return 0;
}