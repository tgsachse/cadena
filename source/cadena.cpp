// Part of Cadena by Tiger Sachse

#include <iostream>
#include <fstream>
#include "cadena.h"

// Node constructor that initializes data, next, and prev.
Node::Node(char data, Node* next, Node* prev) {
    this->data = data;
    this->next = next;
    this->prev = prev;
}

// Constructor for an empty linked list.
Cadena::Cadena(void) {
    initializeMembers();
}

// Constructor for a linked list with an initial node.
Cadena::Cadena(char data) {
    initializeMembers();

    // Convert the char to a string and pass to the insert function.
    std::string str(1, data);
    insert(str, 0);
}

// Constructor for a linked list with several nodes, pulled from data.
Cadena::Cadena(const std::string& data) {
    initializeMembers();
    insert(data, 0);
}

// Constructor for a cadena taken from a filestream.
Cadena::Cadena(std::ifstream& file, char newLineReplacement) {
    initializeMembers();
    
    // Ensure the provided stream is open.
    if (!file.is_open()) {
        throw std::runtime_error("File is not open in Cadena().");
    }

    // Read each character in the stream into the cadena.
    char buffer;
    while (!file.eof()) {
        file.get(buffer);
       
        // If the character is a newline character, append with
        // its replacement. The default is the null character.
        if (buffer == '\n') {
            append(newLineReplacement);
        }
        else {
            append(buffer);
        }
    }
}

// Return the length of the linked list.
int Cadena::getLength(void) const {
    return length;
}

// Return the head of the linked list.
Node* Cadena::getHead(void) const {
    return head;
}

// Insert character at the beginning of the list.
void Cadena::prepend(char data) {
    std::string str(1, data);
    insert(str, 0);
}

// Insert string at the beginning of the list.
void Cadena::prepend(const std::string& data) {
    insert(data, 0);
}

// Insert character at the end of the list.
void Cadena::append(char data) {
    std::string str(1, data);
    insert(str, length);
}

// Insert string at the end of the list.
void Cadena::append(const std::string& data) {
    insert(data, length);
}

// Insert a string into the list at the given index.
void Cadena::insert(const std::string& data, int index) {
    if (data.length() <= 0 || data[0] == '\0') {
        return;
    }
    
    // If attempting to index in reverse (with negatives), then adjust
    // the index to the correct position. -1 results in an index at the
    // very end of the list in this implementation.
    if (index < 0) {
        index += length + 1;
    }
    
    // If the list is empty, create new nodes and set head and tail.
    if (head == NULL) {
        head = generateNodes(data);
        tail = findTail(head);
    }
    // If the data is being prepended to the list, then generate
    // the nodes and change head.
    else if (index <= 0) {
        head = generateNodes(data, head);
    }
    // If the data is meant to be added to an index out of bounds,
    // generate new nodes and append them to the list.
    else if (index >= length) {
        tail->next = generateNodes(data);
        tail = findTail(tail);
    }
    // Else, find the index using the getNode function and then put the
    // data there.
    else {
        Node* current = getNode(index);
        current->next = generateNodes(data, current->next);
    }

    length += data.length();
}

// Initialize members of new list.
void Cadena::initializeMembers(void) {
    head = NULL;
    tail = NULL;
    length = 0;
}

// Get node at index in list.
Node* Cadena::getNode(int index) const {
    Node *current;
  
    if (head == NULL || tail == NULL) {
        throw std::runtime_error("Null pointer exception in getNode().");
    }

    // Check if index is closer to the back of the list than the front.
    if (index > length / 2) {
        int i = length;
        current = tail;
        
        // Iterate backwards from the tail to the desired index.
        while (current->prev != NULL && i > index) {
            current = current->prev;
            i--;
        }
    }
    else {
        int i = 0;
        current = head;
        
        // Iterate forwards from the head to the desired index.
        while (current->next != NULL && i < index) {
            current = current->next;
            i++;
        }
    }

    return current;
}

// Generate a mini-list of nodes and return a pointer to the start.
Node* Cadena::generateNodes(const std::string& data, Node* next) {
    Node* start = new Node(data[0]);
    
    Node* current = start;
    for (int i = 1; i < data.length(); i++) {
        // Create a new node for each character in the string, and
        // set the previous pointer of the new node to the current node.
        current->next = new Node(data[i], NULL, current);
        current = current->next;
    }
    // Point the next pointer of the last node to the provided
    // next node.
    current->next = next;

    return start;
}

// Hunt down the tail of the list. I realize this isn't optimal.
Node* Cadena::findTail(Node* start) {
    if (start == NULL) {
        throw std::runtime_error("Null pointer exception in findTail().");
    }
   
    // Iterate through the list to the end.
    Node* current = start;
    while (current->next != NULL) {
        current = current->next;
    }

    return current;
}

// Allow [bracketed] indexing of list.
char& Cadena::operator[](int index) {
    // Adjust negative index to corresponding positive index.
    if (index < 0) {
        index += length + 1;
    }

    return getNode(index)->data;
}

// Deconstructor of a linked list that destroys all the nodes in the list.
Cadena::~Cadena(void) {
    Node* next;

    // Iterate through all the nodes, deleting them along the way.
    Node* current = head;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
}

// Allow lists to be printed in a standard way.
std::ostream& operator<<(std::ostream& stream, const Cadena& list) {
    Node* current = list.getHead();
    while (current != NULL) {
        stream << current->data;
        current = current->next;
    }

    return stream;
}
