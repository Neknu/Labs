#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct Node {
    Node* dad;
    Node* son;
    Node* next; // brother
    int data;
    int depth;
    Node() {
        dad = nullptr;
        son = nullptr;
        next = nullptr;
        data = 0;
        depth = 0;
    }
};

struct Tree {
    Node* root;
    int length;
    int depth;
    Tree() {
        length = 0;
        depth = 0;
        root = nullptr;
    }
};

Tree* create_empty_tree() {
    Tree* tre = new Tree;
    return tre;
}

Tree* add_root(Tree* tre, int data) {
    Node* root = new Node;
    root->data = data;
    root->depth = 1;
    tre->length = 1;
    tre->depth = 1;
    tre->root = root;

    return tre;
}

Tree* add_new_son(Tree* tre, Node* dad, int data) {
    Node* new_son = new Node;
    new_son->data = data;
    new_son->dad = dad;

    if(!dad->son)
        dad->son = new_son;
    else {
        Node* curr = dad->son;
        while(curr->next)
            curr = curr->next;
        curr->next = new_son;
    }
    if(dad->depth + 1 > tre->depth)
        tre->depth = dad->depth + 1;

    tre->length++;

    return tre;
}

int main() {
    Tree* tre = create_empty_tree();
    add_root(tre, 1);
    add_new_son(tre, tre->root, 2);
    cout << tre->root->data << " " << tre->root->son->data << endl;
    cout << tre->length << " " << tre->depth << endl;
}