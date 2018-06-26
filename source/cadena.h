// Part of Cadena by Tiger Sachse

// Node class to build a dynamic, doubly-linked list (later called a cadena).
// The node pointers really should be private. I'll hopefully
// change this soon.
class Node {
    public:
        char data;
        Node* next;
        Node* prev;
        Node(char, Node* = NULL, Node* = NULL);
};

// Cadena class for dynamically storing strings of arbitrary length.
class Cadena {
    public:
        Cadena(void);
        Cadena(char);
        Cadena(const std::string&);
        Cadena(std::ifstream&, char = '\0');
        int getLength(void) const;
        Node* getHead(void) const;
        void prepend(char);
        void prepend(const std::string&);
        void append(char);
        void append(const std::string&);
        void insert(const std::string&, int);
        bool search(char);
        bool search(const std::string&);
        char& operator[](int);
        ~Cadena(void);

    private:
        int length;
        Node* head;
        Node* tail;

        void initializeMembers(void);
        Node* getNode(int) const;
        Node* generateNodes(const std::string&, Node* = NULL);
        Node* findTail(Node*);
};

// Additional prototypes.
std::ostream& operator<<(std::ostream&, const Cadena&);
