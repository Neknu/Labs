#include <iostream>
#include <string>


using std::string;
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

Node* add_new_son(Tree* tre, Node* dad, int data) {
    Node* new_son = new Node;
    new_son->data = data;
    new_son->dad = dad;
    new_son->depth = dad->depth + 1;

    if(!dad->son)
        dad->son = new_son;
    else {
        Node* curr = dad->son;
        while(curr->next)
            if(curr->data == data)
                return nullptr;
            else
                curr = curr->next;
        curr->next = new_son;
    }
    if(dad->depth + 1 > tre->depth)
        tre->depth = dad->depth + 1;

    tre->length++;

    return new_son;
}

Node* find_son(Node* dad, int data) {
    Node* curr = dad->son;
    while(curr)
        if(curr->data == data)
            return curr;
        else
            curr = curr->next;
    return nullptr;
}


void cout_operations() {
    cout << endl;
    cout << "Select operation:" << "\n";
    cout << "create_tree" << "\n";
    cout << "add_son" << "\n";
    cout << "print_tree" << "\n";
    cout << "exit" << "\n";
}


void cout_finding_operations() {
    cout << endl;
    cout << "Select operation:" << "\n";
    cout << "go_further" << "\n";
    cout << "select_this" << "\n";
}

Node* find_node_in_tree(Tree* tre) {
    Node* curr = tre->root;
    string finding;
    for(int i = 1; i <= tre->depth; i++) {

        cout << "Your current depth = " << curr->depth << "\n";
        cout << "Your current Node(data) = " << curr->data << "\n";

        cout_finding_operations();
        cin >> finding;
        if (finding == "select_this") {
            return curr;
        }
        if(finding == "go_further") {
            cout << "enter data for go to the son:" << "\n";
            int data;
            cin >> data;
            curr = find_son(curr, data);
            if(!curr) {
                cout << "this son doesn't exist!";
                break;
            }
        }
    }
    return nullptr;
}

void cout_path_to_node(Node* curr) {
    for(int i = 0; i < curr->depth; i++)
        cout << " --";
    cout << curr->data << endl;
}

void print_tree_rekurs(Tree* tre, Node* root) {
        Node* curr = root->son;
        while(curr) {
            print_tree_rekurs(tre, curr);
            curr = curr->next;
        }
        cout_path_to_node(root);
}


Node* add_son_to_tree(Tree* tre) {

    Node* curr = find_node_in_tree(tre);
    if(!curr) {
        cout << "something went wrong, redo adding";
        return nullptr;
    }
    cout << "enter data for adding son to this dad:" << "\n";
    int data;
    Node* new_son;
    cin >> data;
    new_son = add_new_son(tre, curr, data);
    if(!new_son)
        cout << "this son already exists!" << "\n";
    return new_son;
}

int main() {
    string operation;
    Tree *tre;
    while(true) {
        cout_operations();
        cin >> operation;

        if (operation == "create_tree") {
            cout << "enter root data:" << "\n";
            int data;
            cin >> data;
            tre = create_empty_tree();
            add_root(tre, data);
        }
        else if (operation == "add_son") {
            if(!tre) {
                cout << "create tree at first!" << "\n";
                continue;
            }
            add_son_to_tree(tre);
        }
        else if (operation == "print_tree") {
            print_tree_rekurs(tre, tre->root);
        }
        else if (operation == "exit") {
            return 0;
        }

    }
}