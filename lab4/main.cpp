#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <cstring>

using std::string;
using std::cin;
using std::cout;
using std::endl;


//block 0
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


//block 1 and 2
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

void set_correct_depth(Tree* tre, Node* root, int depth) {
    Node* curr = root->son;
    cout << root->data;
    while(curr) {
        set_correct_depth(tre, curr, depth + 1);
        curr = curr->next;
    }
    root->depth = depth;
    tre->depth = std::max(tre->depth, depth);
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

//block 3

void delete_son(Tree* tre, Node* to_del) {
    if(tre->length == 1) {
        delete to_del;
        delete tre;
    }
    if(to_del->next == nullptr) {
        to_del->dad->son = to_del->son;
        Node* curr = to_del->son;
        while(curr) {
            curr->dad = to_del->dad;
            curr = curr->next;
        }
    }
    else if(to_del->dad->son->data == to_del->data) {  // data is unique at one level
        to_del->dad->son = to_del->son;
        Node* curr = to_del->son;
        if(curr) {
            while (curr->next) {
                curr->dad = to_del->dad;
                curr = curr->next;
            }
            curr->dad = to_del->dad;
            curr->next = to_del->next;
        }
    }
    else {
        Node* son = to_del->dad->son;
        while(son->next->data != to_del->data && son->next != nullptr)
            son = son->next;
        Node* curr = to_del->son;
        if(curr) {
            son->next = curr;
            while (curr->next) {
                curr->dad = to_del->dad;
                curr = curr->next;
            }
            curr->dad = to_del->dad;
            curr->next = to_del->next;
        }
        else{
            son->next = to_del->next;
        }
    }
    delete to_del;
    tre->length--;
    tre->depth = 1;
    set_correct_depth(tre, tre->root, 1);
}

Tree* delete_son_from_tree(Tree* tre) {

    Node* curr = find_node_in_tree(tre);
    if(!curr) {
        cout << "something went wrong, redo deleting";
        return tre;
    }
    delete_son(tre, curr);
    return tre;
}

Tree* build_demo_tree() {
    Tree* tre = create_empty_tree();
    tre = add_root(tre, 1);
    add_new_son(tre, tre->root, 2);
    add_new_son(tre, tre->root, 3);
    add_new_son(tre, tre->root->son, 4);
    add_new_son(tre, tre->root->son, 5);
    add_new_son(tre, tre->root->son, 6);
    add_new_son(tre, tre->root->son->son->next, 7);
    add_new_son(tre, tre->root->son->son->next, 8);
    return tre;
}








// second part - BINARY TREE
// here only root is saving all tree


//block 4
struct node {
    int key;
    node *left, *right;

    bool isThreaded;
};


node* newNode(int item) {
    node *temp =  new node;
    temp->key = item;
    temp->left = temp->right = nullptr;
    return temp;
}


void printBinTree(struct node *root, int depth) {
    if (root != nullptr)
    {
        printBinTree(root->left, depth + 1);
        for(int i = 0; i < depth; i++)
            cout << " --";
        cout << root->key << "\n";
        printBinTree(root->right, depth + 1);
    }
}


node* insert(node* node, int key) {

    if (node == nullptr) return newNode(key);

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}


//block 5

void populateQueue(node *root, std::queue <node *> *q) {
    if (root == nullptr) return;
    if (root->left)
        populateQueue(root->left, q);
    q->push(root);
    if (root->right)
        populateQueue(root->right, q);
}


void createThreadedUtil(node *root, std::queue <node *> *q)
{
    if (root == nullptr) return;

    if (root->left)
        createThreadedUtil(root->left, q);
    q->pop();

    if (root->right)
        createThreadedUtil(root->right, q);

    else
    {
        root->right = q->front();
        root->isThreaded = true;
    }
}

//convert binary to threaded
void createThreaded(node *root) {
    std::queue <node *> q;
    populateQueue(root, &q);
    createThreadedUtil(root, &q);
}


node *leftMost(node *root, int &depth) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
        depth++;
    }
    return root;
}


void inOrder(node *root) {
    if (root == nullptr) return;

    int depth = 1;
    node *cur = leftMost(root, depth);

    while (cur != nullptr)
    {
        for(int i = 0; i < depth; i++)
            cout << " --";
        cout << cur->key << endl;

        if (cur->isThreaded)
            cur = cur->right;
        else {
            depth = 1;
            cur = leftMost(cur->right, depth);
        }
    }
}

node* build_bin_tree() {
    node *root = nullptr;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printBinTree(root, 1);
    return root;
}


//block 6


// An expression tree node
struct et
{
    char value;
    et* left, *right;
};


bool isOperator(char c)
{
    if (c == '+' || c == '-' ||
        c == '*' || c == '/' ||
        c == '^')
        return true;
    return false;
}


void inorder(et *t)
{
    if(t)
    {
        inorder(t->left);
        cout << t->value;
        inorder(t->right);
    }
}


et* new_node(int v)
{
    et *temp = new et;
    temp->left = temp->right = NULL;
    temp->value = v;
    return temp;
};


et* constructTree(char postfix[])
{
    std::stack<et *> st;
    et *t, *t1, *t2;

    for (int i=0; i<strlen(postfix); i++)
    {

        if (!isOperator(postfix[i]))
        {
            t = new_node(postfix[i]);
            st.push(t);
        }
        else
        {
            t = new_node(postfix[i]);

            t1 = st.top();
            st.pop();
            t2 = st.top();
            st.pop();

            t->right = t1;
            t->left = t2;

            st.push(t);
        }
    }

    t = st.top();
    st.pop();

    return t;
}

void cout_operations() {
    cout << endl;
    cout << "Select operation:" << "\n";
    cout << "create_tree" << "\n";
    cout << "add_son" << "\n";
    cout << "delete_son" << "\n";
    cout << "build_demo_tree" << "\n";
    cout << "print_tree" << "\n";
    cout << "exit" << "\n";
}

void cout_bin_operations() {
    cout << endl;
    cout << "Select operation:" << "\n";
    cout << "insert" << "\n";
    cout << "build_demo_tree" << "\n";
    cout << "print" << "\n";
    cout << "exit" << "\n";
}

void cout_types_of_tree() {
    cout << endl;
    cout << "Select type of tree:" << "\n";
    cout << "binary" << "\n";
    cout << "common" << "\n";
}

int main() {
    string operation, type;
    Tree *tre;
    node* root = nullptr;
    cout_types_of_tree();
    cin >> type;
    while(true) {
        if(type == "common") {
            cout_operations();
            cin >> operation;

            if (operation == "create_tree") {
                cout << "enter root data:" << "\n";
                int data;
                cin >> data;
                tre = create_empty_tree();
                add_root(tre, data);
            } else if (operation == "add_son") {
                if (!tre) {
                    cout << "create tree at first!" << "\n";
                    continue;
                }
                add_son_to_tree(tre);
            } else if (operation == "delete_son") {
                if (!tre) {
                    cout << "create tree at first!" << "\n";
                    continue;
                }
                delete_son_from_tree(tre);
            } else if (operation == "build_demo_tree") {
                tre = build_demo_tree();
            } else if (operation == "print_tree") {
                if (!tre) {
                    cout << "create tree at first!" << "\n";
                    continue;
                }
                print_tree_rekurs(tre, tre->root);
            } else if (operation == "exit") {
                return 0;
            }
        }
        else if(type == "binary") {
            int key;
            cout_bin_operations();
            cin >> operation;
            if (operation == "insert") {
                cout << "Enter data:" << "\n";
                cin >> key;
                if(!root)
                    root = insert(root, key);
                else
                    insert(root, key);
            } else if (operation == "build_demo_tree") {
                root = build_bin_tree();
            } else if (operation == "print") {
                printBinTree(root, 1);
            } else if (operation == "exit") {
                return 0;
            }
        }

    }
}