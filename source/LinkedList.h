// Node class to build a dynamic, doubly-linked list.
// The node pointers really should be private. I'll hopefully
// change this soon.
class Node {
    public:
        char data;
        Node* next;
        Node* prev;
        Node(char, Node* = NULL, Node* = NULL);
};

// LinkedList class for dynamically storing strings of arbitrary length.
class LinkedList {
    public:
        LinkedList(void);
        LinkedList(char);
        LinkedList(const std::string&);
        int getLength(void) const;
        Node* getHead(void) const;
        void prepend(char);
        void prepend(const std::string&);
        void append(char);
        void append(const std::string&);
        void insert(const std::string&, int);
        char& operator[](int);
        ~LinkedList(void);

    private:
        int length;
        Node* head;
        Node* tail;

        void initializeMembers(void);
        Node* getNode(int) const;
        Node* generateNodes(const std::string&, Node* = NULL);
        Node* findTail(Node*);
};

std::ostream& operator<<(std::ostream&, const LinkedList&);
