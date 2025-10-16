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

        Node* temp = head; // temp pointer created to help with traversing list
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

        Node* temp = head; // for traversing the list, starts at head of list
        
        while (temp && temp->data != value) // while temp exists, and the data of temp is not the same as value
            temp = temp->next; // temp is set to next node in list

        if (!temp) return; // if temp does not exist, there is no node where data == value, exits

        // if none of the if statements run, then temp exists where temp->data == value
        if (temp->prev) // if there is another node before temp
            temp->prev->next = temp->next; // node after temp is set to be after previous node
        else // if there is no node before temp, that means it is the head
            head = temp->next; // node after temp becomes new head

        if (temp->next) // if there is a node after temp
            temp->next->prev = temp->prev; // node after temp is set to be befire previous node
        else // if there is no node after temp, then temp is the tail
            tail = temp->prev; // node before temp becomes new tail

        delete temp; // delete temp node and value
    }

    void delete_pos(int pos) { // deletes node based on the given position
        if (!head) { // if head == nullptr, list is empty
            cout << "List is empty." << endl; // display error message for user
            return; // exit
        }
    
        if (pos == 1) { // if given position is the head node
            pop_front(); // use pop_front to remove head node
            return; // exit
        }
    
        Node* temp = head; // for traversing list
    
        for (int i = 1; i < pos; i++){ // loops until desired position is reached
            if (!temp) { // if temp does not exist, position is invalid
                cout << "Position doesn't exist." << endl; // displays user statement
                return; // exits
            }
            else // temp does exist
                temp = temp->next; // temp is set to next node
        }
        if (!temp) { // if temp does not exist, position is invalid
            cout << "Position doesn't exist." << endl; // displays user statement
            return; // exits
        }

        if (!temp->next) { // if there is no node after temp, temp is the tail
            pop_back(); // deletes the tail node
            return; // exits
        }
    
        Node* tempPrev = temp->prev; // new node set to node before temp
        tempPrev->next = temp->next; // node after temp is now after tempPrev
        temp->next->prev = tempPrev; // tempPrev is now before node after temp
        delete temp; // deletes temp node and value
    }

    void push_back(int v) { // adds new node to the back
        Node* newNode = new Node(v); // creates new node with data = value
        if (!tail) // if tail does not exist, list is empty
            head = tail = newNode; // newNode becomes first + last node in list
        else { // if tail does exist (at least 1 other node in list)
            tail->next = newNode; // tail is before newNode
            newNode->prev = tail; // newNode is after the previous tail node
            tail = newNode; // newNode becomes the new tail node
        }
    }
    
    void push_front(int v) { // adds new node to the front
        Node* newNode = new Node(v); // creates new node with data = value
        if (!head) // if head does not exist, list is empty
            head = tail = newNode; // newNode becomes first + last node in list
        else { // if head does exist (at least 1 node in list)
            newNode->next = head; // newNode is before head
            head->prev = newNode; // previous head is now after newNode
            head = newNode; // newNode becomes new head node
        }
    }
    
    void pop_front() { // deletes the head node

        if (!head) { // if head does not exist, list is empty
            cout << "List is empty." << endl; // error message for user
            return; // exits code
        }

        Node * temp = head; // pointer that points to head node

        if (head->next) { // if there is a node after head
            head = head->next; // new head becomes node that was after head
            head->prev = nullptr; // no node is before the head node
        }
        else // if there is only one node in list
            head = tail = nullptr; // list is empty
        delete temp; // deletes temp pointer for storage
    }

    void pop_back() { // deletes the tail node
        if (!tail) { // if tail does not exist, list is empty
            cout << "List is empty." << endl; // error message for user
            return; // exits code
        }
        Node * temp = tail; // pointer that points to tail node

        if (tail->prev) { // if there is a node before the tail
            tail = tail->prev; // new tail becomes node that was before tail
            tail->next = nullptr; // no node is after tail node
        }
        else // if there is only one node in list
            head = tail = nullptr; // list is empty
        delete temp; // deletes temp pointer for storage
    }

    ~DoublyLinkedList() { // destructor for deleting the linked list
        while (head) { // while the head node exists
            Node* temp = head; // declare temp node that points to head
            head = head->next; // new head is the one after head node
            delete temp; // previous head node gets deleted
        }
    }
    void print() { // displays all elements in order from head to tail
        Node* current = head; // for traversing list
        if (!current) { // if current doesn't exist, list is empty
            cout << "List is empty." << endl; // display message for user
            return; // exit code
        }
        while (current) { // while the current node exists
            cout << current->data << " "; // output the value of the node
            current = current->next; // set current to next node
        }
        cout << endl; // move to new line
    }

    void print_reverse() { // displays all elements in order from tail to head
        Node* current = tail; // for traversing list
        if (!current) { // if current doesn't exist, list is empty
            cout << "List is empty." << endl; // display message for user
            return; // exit code
        }
        while (current) { // while the current node exists
            cout << current->data << " "; // output the value of the node
            current = current->prev; // set current node to previous node in list
        }
        cout << endl; // mpve to new line
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}