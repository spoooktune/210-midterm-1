// COMSC 210 | Midterm 1 | Amrutha Sriprasana
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node { // declaring blueprint for each node (item) in linked list
        int data; // actual data value for each nodee
        Node* prev; // points to previous node in the linked list
        Node* next; // points to next node in linked list
        Node(int val, Node* p = nullptr, Node* n = nullptr) { // initializing node w/ at least a specified val - if no previous/next node pointers given, they default to nullptr
            data = val; // set desired value for data
            prev = p; // setting previous and next node pointers determines location for this node
            next = n;
        }
    };

    Node* head; // start of linked list
    Node* tail; // end of linked list

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // initializes the linked list as empty (since head + tail point to nullptr)

    void insert_after(int value, int position) { // creates a new node w/ value as data var, places after specified position in linked list
        if (position < 0) { // if the position is < 0, it cannot exist in the list, so must check if position is valid
            cout << "Position must be >= 0." << endl; // error message to tell user position is invalid
            return;
        }

        Node* newNode = new Node(value); // creating new node, data = value, prev = nullptr, next = nullptr
        if (!head) { // if there is no head -> if the list is empty
            head = tail = newNode; // makes newNode the new head
            return;
        }

        Node* temp = head; // temp pointer created to help with traversing array
        for (int i = 0; i < position && temp; ++i) // traverses array until specified position is reached or until temp = nullptr
            temp = temp->next; // sets temp as pointer to next node in the linked list

        if (!temp) { // if temp becomes nullptr -> specified position is greater than the # of elements in list
            cout << "Position exceeds list size. Node not inserted.\n"; // display error message for user
            delete newNode; // frees up storage space
            return;
        }

        // if previous if statements are not called, then position is valid, newNode can be inserted after it
        newNode->next = temp->next; // newNode points to the node that was previously after temp 
        newNode->prev = temp; // temp is node at specified position, so it is before newNode
        if (temp->next) // if temp has a node specified after it (temp->next is not nullptr)
            temp->next->prev = newNode; // sets node that was previously after temp to be after newNode
        else // temp->next = nullptr, so temp was the tail
            tail = newNode; // newNode becomes the new tail
        temp->next = newNode; // temp points to the new tail
    }

    void delete_val(int value) { // delete's node based on the data var of Node
        if (!head) return; // if there is no head, there is nothing to delete, code exits

        Node* temp = head; // for traversing the array, starts at head of list
        
        while (temp && temp->data != value) // while temp exists, and the data of temp is not the same as value
            temp = temp->next; // temp is set to next node in list

        if (!temp) return; // if temp does not exist, there is no node where data == value, exits

        // if none of the if statements run, then temp exists where temp->data == value
        if (temp->prev) // if there is another node before temp
            temp->prev->next = temp->next; // node after temp is set to be after previous node
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}