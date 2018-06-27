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

// Constructor for an empty cadena.
Cadena::Cadena(void) {
    initializeMembers();
}

// Constructor for a cadena with an initial node.
Cadena::Cadena(char data) {
    initializeMembers();

    // Convert the char to a string and pass to the insert function.
    std::string str(1, data);
    insert(str, 0);
}

// Constructor for a cadena with several nodes, pulled from data.
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

// Return the length of the cadena.
int Cadena::getLength(void) const {
    return length;
}

// Return the head of the cadena.
Node* Cadena::getHead(void) const {
    return head;
}

// Insert character at the beginning of the cadena.
void Cadena::prepend(char data) {
    std::string str(1, data);
    insert(str, 0);
}

// Insert string at the beginning of the cadena.
void Cadena::prepend(const std::string& data) {
    insert(data, 0);
}

// Insert character at the end of the cadena.
void Cadena::append(char data) {
    std::string str(1, data);
    insert(str, length);
}

// Insert string at the end of the cadena.
void Cadena::append(const std::string& data) {
    insert(data, length);
}

// Insert a string into the cadena at the given index.
void Cadena::insert(const std::string& data, int index) {
    if (data.length() <= 0 || data[0] == '\0') {
        return;
    }
    
    // If attempting to index in reverse (with negatives), then adjust
    // the index to the correct position. -1 results in an index at the
    // very end of the cadena in this implementation.
    if (index < 0) {
        index += length + 1;
    }
    
    // If the cadena is empty, create new nodes and set head and tail.
    if (head == NULL) {
        head = generateNodes(data);
        tail = findTail(head);
    }
    // If the data is being prepended to the cadena, then generate
    // the nodes and change head.
    else if (index <= 0) {
        head = generateNodes(data, head);
    }
    // If the data is meant to be added to an index out of bounds,
    // generate new nodes and append them to the cadena.
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

// Find a character in a cadena.
int Cadena::search(char pattern) {
    std::string str(1, pattern);

    return search(str);
}

// Find a pattern in the cadena.
int Cadena::search(const std::string& pattern) {
    if (pattern.length() < 1 || pattern.length() > length) {
        return 0;
    }

    int* pi = generatePiTable(pattern);

    int j = 0;
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        // Match as many characters as possible until the cadena terminates
        // or all characters in the pattern have been matched.
        while (current->data == pattern[j]) {
            current = current->next;
            j += 1;

            if (current == NULL || j >= pattern.length()) {
                break;
            }
        }

        // These conditions occur after the above loop consumes all matching
        // characters. At this point, the algorithm has either found a match,
        // found a non-matching character, or reached the end of the cadena.
        // If the pattern index j is at or beyond the length of the pattern,
        // then the algorithm has found a match.
        if (j >= pattern.length()) {
            count++;
            j = pi[j - 1];
        }
        else if (current == NULL) {
            break;
        }
        // Else no match was found. If the pattern index j is zero, then the
        // pattern is reset all the way to the beginning and the algorithm should
        // move on to the next character in the cadena. Otherwise the algorithm should
        // attempt to reset the pattern index to an index where it can start checking
        // characters again, but not to zero (if possible). This index is specified
        // in the pi table. See generatePiTable() for details.
        else {
            if (j == 0) {
                current = current->next;
            }
            else {
                j = pi[j - 1];
            }
        }
    }
    
    delete []pi;

    return count;
}

// Allow [bracketed] indexing of cadena.
char& Cadena::operator[](int index) {
    // Adjust negative index to corresponding positive index.
    if (index < 0) {
        index += length + 1;
    }

    return getNode(index)->data;
}

// Deconstructor of a cadena that destroys all the nodes in the cadena.
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

// Initialize members of new cadena.
void Cadena::initializeMembers(void) {
    head = NULL;
    tail = NULL;
    length = 0;
}

// Get node at index in cadena.
Node* Cadena::getNode(int index) const {
    Node *current;
  
    if (head == NULL || tail == NULL) {
        throw std::runtime_error("Null pointer exception in getNode().");
    }

    // Check if index is closer to the back of the cadena than the front.
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

// Hunt down the tail of the cadena. I realize this isn't optimal.
Node* Cadena::findTail(Node* start) {
    if (start == NULL) {
        throw std::runtime_error("Null pointer exception in findTail().");
    }
   
    // Iterate through the cadena to the end.
    Node* current = start;
    while (current->next != NULL) {
        current = current->next;
    }

    return current;
}

// Generate a pi table from a pattern for use in the KMP search algorithm.
int* Cadena::generatePiTable(const std::string& pattern) {
    int* pi = new int[pattern.length()]();

    int i = 1;
    int length = 0;
    // The values in the table describe the longest length of a suffix in
    // the pattern at index i that is also a prefix. For example in the pattern
    // 'aabaab' at index 4, the longest prefix that is also a suffix is 'aa' (realize
    // this is for the subpattern 'aabaa'). The length of this prefix/suffix is 2, so
    // that goes into the table at index 4. This is useful because when the KMP
    // algorithm finds a mismatch, it can simply 'shift' the pattern up by the value
    // in the pi table at the correct index without having to rescan characters that
    // would ultimately end up matching again. It's quite difficult to explain in a
    // comment with no pictures. :)
    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            pi[i] = length;
            i++;
        }
        else if (length != 0) {
            length = pi[length - 1];
        }
        else {
            i++;
        }
    }

    return pi;
}

// Allow cadenas to be printed in a standard way.
std::ostream& operator<<(std::ostream& stream, const Cadena& cadena) {
    Node* current = cadena.getHead();
    while (current != NULL) {
        stream << current->data;
        current = current->next;
    }

    return stream;
}
