struct Node {
    int data;
    Node* next;
};

class LinkedList {
    public:
        Node* head;
        
        void insertFront(int data);
        void display();
};