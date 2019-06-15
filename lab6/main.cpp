#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <functional>
#include <algorithm>
#include <iomanip>


#include<windows.h>
#include<stdio.h>
#include<tchar.h>


// Use to convert bytes to MB
#define DIV 1048576
#define WIDTH 7


using std::string;
using std::cin;
using std::cout;
using std::endl;

int const RAND = 20;
int const MAX = 1000000;

int rand_num(int max) {
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(0, max);

    return int(dist(gen));
}


void print_memory() {
    MEMORYSTATUSEX statex;

    statex.dwLength = sizeof (statex);

    GlobalMemoryStatusEx (&statex);


    _tprintf (TEXT("There is  %*ld percent of memory in use.\n"),WIDTH, statex.dwMemoryLoad);
    _tprintf (TEXT("There are %*I64d total Mbytes of physical memory.\n"),WIDTH,statex.ullTotalPhys/DIV);
    _tprintf (TEXT("There are %*I64d free Mbytes of physical memory.\n"),WIDTH, statex.ullAvailPhys/DIV);
    _tprintf (TEXT("There are %*I64d total Mbytes of paging file.\n"),WIDTH, statex.ullTotalPageFile/DIV);
    _tprintf (TEXT("There are %*I64d free Mbytes of paging file.\n"),WIDTH, statex.ullAvailPageFile/DIV);
    _tprintf (TEXT("There are %*I64d total Mbytes of virtual memory.\n"),WIDTH, statex.ullTotalVirtual/DIV);
    _tprintf (TEXT("There are %*I64d free Mbytes of virtual memory.\n"),WIDTH, statex.ullAvailVirtual/DIV);
    _tprintf (TEXT("There are %*I64d free Mbytes of extended memory.\n"),WIDTH, statex.ullAvailExtendedVirtual/DIV);
}

//task 1

struct Node {
    string data;
    Node* next;
    Node(){
        data = "";
        next = nullptr;
    };
};

struct LinkedList {
    Node* root;
    int length;
    LinkedList(){
        root = nullptr;
        length = 0;
    }
};

LinkedList* create_linked_list(){
    LinkedList* list = new LinkedList;
    return list;
}

Node* create_new_node(string data, Node* next) {
    Node* temp = new Node;
    temp->data = data;
    temp->next = next;
    return temp;
}

LinkedList* add_element_linked_list(LinkedList* list, string data) {
    if(list->root == nullptr) {
        list->root = create_new_node(data, nullptr);
    }
    else {
        if(data < list->root->data) {
            list->root = create_new_node(data, list->root);
        }
        else {
            Node* curr = list->root;
            if (curr->data == data)
                return list;
            while(curr->next && data > curr->next->data) {
                curr = curr->next;
            }
            if(curr->next) {
                if (data == curr->next->data)
                    return list;
                curr->next = create_new_node(data, curr->next);
            }
            else {
                curr->next = create_new_node(data, curr->next);
            }

        }
    }
    list->length++;
    return list;
}

Node* find_element_linked_list(LinkedList* list, string data) {
    Node* curr = list->root;
    while(curr) {
        if(curr->data > data)
            return nullptr;
        if(curr->data == data)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

Node* find_element_diapason_linked_list(LinkedList* list, string start, string end) {
    Node* curr = list->root;
    while(curr) {
        if(curr->data > end)
            return nullptr;
        if(start <= curr->data && curr->data <= end)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

LinkedList* delete_element_linked_list(LinkedList* list, string data) {
    Node* finded = find_element_linked_list(list, data);
    if(finded == nullptr)
        return list;
    else {
        swap(finded->data, finded->next->data);
        Node* temp = finded->next;
        finded->next = temp->next;
        delete temp;
    }
    list->length--;
    return list;
}

void print_linked_list(LinkedList* list) {
    cout << endl;
    Node* curr = list->root;
    while(curr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

LinkedList* create_random_linked_list(int count) {
    LinkedList* list = create_linked_list();
    string word;
    for(int i = 0; i < count; i++) {
        int rand = rand_num(RAND) + 1;
        word = "";
        for(int j = 0; j < rand; j++)
            word += char(65 + rand_num(rand) + 1);
        add_element_linked_list(list, word);
    }
    return list;
}

void demo_linked_list(int count) {
    LinkedList* list = create_random_linked_list(count);
    cout << "created random list" << endl;
    print_linked_list(list);
    cout << "deleted 1/4 elements" << endl;
    for(int i = 0; i < list->length / 4; i ++)
        delete_element_linked_list(list, list->root->data);

    print_linked_list(list);
}

void benchmark_linked_list() {
    int N = 6;
    using namespace std::chrono;
    duration<double> time_span;
    float t;
    do {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        LinkedList* list = create_random_linked_list(N);

        for(int i = 0; i < N / 2; i ++)
            delete_element_linked_list(list, list->root->data);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        time_span = duration_cast<duration<double>>(t2 - t1);
        t = time_span.count();
        N = N * 2;
    }

    while(t < 5);
    print_memory();
    cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
    cout << "N = " << N << "\n";
}

// task 2

struct ArrayList {
    string arr[MAX];
    int length;
    ArrayList() {
        for(int i = 0; i < MAX; i++)
            arr[i] = "";
        length = 0;
    }
};

ArrayList* create_array_list() {
    ArrayList* arr = new ArrayList;
    return arr;
}

ArrayList* shift_array_up(ArrayList* arr, int num) {
    for(int i = arr->length - 1; i >= num; i--)
        arr->arr[i + 1] = arr->arr[i];
    return arr;
}

ArrayList* add_element_array_list(ArrayList* arr, string data) {
    if(arr->length == 0)
        arr->arr[0] = data;
    else {
        int i = 0;
        while (i < arr->length && arr->arr[i] < data) {
            i++;
        }
        if(i == arr->length) {
            arr->arr[i] = data;
        }
        else {
            if(arr->arr[i] == data) {
                return arr;
            }
            else {
                shift_array_up(arr, i);
                arr->arr[i] = data;
            }
        }
    }
    arr->length++;
    return arr;
}

int binarySearch(string arr[], int l, int r, string x)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid - 1, x);

        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

int find_element_array_list(ArrayList* arr, string data) {
     return binarySearch(arr->arr, 0, arr->length - 1, data);
}

int find_element_diapason_array_list(ArrayList* arr, string start, string end) {
    for(int i = 0; i < arr->length; i ++) {
        if(arr->arr[i] > end)
            return -1;
        if (start <= arr->arr[i] && arr->arr[i] <= end)
            return i;
    }
    return -1;
}

ArrayList* shift_array_down(ArrayList* arr, int num) {
    for(int i = num; i < arr->length - 1; i++)
        arr->arr[i] = arr->arr[i + 1];
    return arr;
}

ArrayList* delete_element_array_list(ArrayList* arr, string data) {
    int curr = find_element_array_list(arr, data);
    if (curr < 0)
        return arr;
    else {
        shift_array_down(arr, curr);
    }
    arr->length--;
    return arr;
}

void print_array_list(ArrayList* arr) {
    cout << endl;
    for(int i = 0; i < arr->length; i ++) {
        cout << arr->arr[i] << " ";
    }
    cout << endl;
}

ArrayList* create_random_array_list(int count) {
    ArrayList* arr = create_array_list();
    string word;
    for(int i = 0; i < count; i++) {
        int rand = rand_num(RAND) + 1;
        word = "";
        for(int j = 0; j < rand; j++)
            word += char(65 + rand_num(rand) + 1);
        add_element_array_list(arr, word);
    }
    return arr;
}

void demo_array_list(int count) {
    ArrayList* arr = create_random_array_list(count);
    cout << "created random arr" << endl;
    print_array_list(arr);
    cout << "deleted 1/4 elements" << endl;
    for(int i = 0; i < arr->length / 4; i ++)
        delete_element_array_list(arr, arr->arr[i]);

    print_array_list(arr);
}

void benchmark_array_list() {
    int N = 6;
    using namespace std::chrono;
    duration<double> time_span;
    float t;
    do {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        ArrayList* arr = create_random_array_list(N);

        for(int i = 0; i < N / 2; i ++)
            delete_element_array_list(arr, arr->arr[i]);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        time_span = duration_cast<duration<double>>(t2 - t1);
        t = time_span.count();
        N = N * 2;
    }

    while(t < 5);
    print_memory();
    cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
    cout << "N = " << N << "\n";
}


// task 3

struct BinNode{
    BinNode* left;
    BinNode* right;
    string data;
};

struct BinTree{
    BinNode* root;
    int count_of_elements;
    BinTree(){
        root = nullptr;
        count_of_elements = 0;
    }
};

BinTree* create_bin_tree() {
    BinTree* bin = new BinTree;
    return bin;
}


BinNode* newNode(string item) {
    BinNode *temp =  new BinNode;
    temp->data = item;
    temp->left = temp->right = nullptr;
    return temp;
}



BinNode* add_element_bin(BinNode* BinNode, string key) {

    if (BinNode == nullptr) return newNode(key);

    if (key < BinNode->data)
        BinNode->left  = add_element_bin(BinNode->left, key);
    else if (key > BinNode->data)
        BinNode->right = add_element_bin(BinNode->right, key);

    return BinNode;
}

BinTree* add_element_bin_tree(BinTree* bin, string key) {
    BinNode* new_node;
    new_node = add_element_bin(bin->root, key);
    if(bin->root == nullptr) {
        bin->root = new_node;
    }
    if (new_node) {
        bin->count_of_elements++;
    }
    return bin;
}

BinNode* find_element_bin_tree(BinTree* bin, string key) {
    BinNode* BinNode = bin->root;
    while(BinNode) {
        if(BinNode->data == key) {
            return BinNode;
        }
        if(BinNode->data < key) {
            BinNode = BinNode->right;
        }
        else {
            if (BinNode->data > key) {
                BinNode = BinNode->left;
            }
        }
    }
    return nullptr;
}

BinNode* find_element_dad_bin_tree(BinTree* bin, string key) {
    BinNode* BinNode = bin->root;
    while(BinNode) {
        if(BinNode->left)
            if(BinNode->left->data == key)
                return BinNode;
        if(BinNode->right)
            if(BinNode->right->data == key)
                return BinNode;
        if(BinNode->data < key) {
            BinNode = BinNode->right;
        }
        else {
            if (BinNode->data > key) {
                BinNode = BinNode->left;
            }
        }
    }
    return nullptr;
}

BinNode* find_element_diapason_bin_tree(BinTree* bin, string start, string end) {
    BinNode* BinNode = bin->root;
    while(BinNode) {
        if(start <= BinNode->data && BinNode->data <= end)
            return BinNode;
        if(BinNode->data < end)
            BinNode = BinNode->right;
        else
        if(BinNode->data > start)
            BinNode = BinNode->left;
    }
    return nullptr;
}

BinTree* swap_delete_bin_node(BinTree* bin, BinNode* to_del, BinNode* temp) {
    swap(to_del->data, temp->data);
    to_del->left = temp->left;
    to_del->right = temp->right;
    delete temp;
    return bin;
}

BinTree* delete_element_bin_tree(BinTree* bin, string data) {
    BinNode* to_del = find_element_bin_tree(bin, data);
    if(!to_del)
        return bin;
    else {
        if(to_del->right == nullptr && to_del->left == nullptr) {
            BinNode* dad = find_element_dad_bin_tree(bin, data);
            if(dad->left->data == data)
                dad->left = nullptr;
            else
                dad->right = nullptr;
            delete to_del;
        }
        else {
            if (to_del->right == nullptr) {
                BinNode* temp = to_del->left;
                swap_delete_bin_node(bin, to_del, temp);
            }
            else {
                if(to_del->left == nullptr) {
                    BinNode* temp = to_del->right;
                    swap_delete_bin_node(bin, to_del, temp);
                }
                else {
                    BinNode* curr = to_del->left;
                    while(curr->right)
                        curr = curr->right;
                    swap(to_del->data, curr->data);
                    if(curr->left) {
                        BinNode *temp = curr->left;
                        swap_delete_bin_node(bin, curr, temp);
                    }
                    else {
                        BinNode* dad = find_element_dad_bin_tree(bin, curr->data);
                        if(dad->left->data == data)
                            dad->left = nullptr;
                        else
                            dad->right = nullptr;
                        delete curr;
                    }
                }
            }
        }
    }
    return bin;
}

BinTree* create_random_bin_tree(int count) {
    BinTree* bin = create_bin_tree();
    string word;
    for(int i = 0; i < count; i++) {
        int rand = rand_num(RAND) + 1;
        word = "";
        for(int j = 0; j < rand; j++)
            word += char(65 + rand_num(rand) + 1);
        add_element_bin_tree(bin, word);
    }
    return bin;
}

void print_bin(BinNode *root, int depth) {
    if (root != nullptr)
    {
        print_bin(root->left, depth + 1);
        for(int i = 0; i < depth; i++)
            cout << " --";
        cout << root->data << "\n";
        print_bin(root->right, depth + 1);
    }
}

void print_bin_tree(BinTree* bin) {
    print_bin(bin->root, 1);
}


void demo_bin_tree(int count) {
    BinTree* bin = create_random_bin_tree(count);
    cout << "created random bin" << endl;
    print_bin_tree(bin);
    cout << "deleted 1/4 elements" << endl;
    for(int i = 0; i < bin->count_of_elements / 4; i ++)
        delete_element_bin_tree(bin, bin->root->data);

    print_bin_tree(bin);
}

void benchmark_bin_tree() {
    int N = 6;
    using namespace std::chrono;
    duration<double> time_span;
    float t;
    do {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        BinTree* bin = create_random_bin_tree(N);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        time_span = duration_cast<duration<double>>(t2 - t1);
        t = time_span.count();
        N = N * 2;
    }

    while(t < 5);
    print_memory();
    cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
    cout << "N = " << N << "\n";
}


//task 4


struct AVLNode {
        string data;
        AVLNode* left;
        AVLNode* right;

        ~AVLNode() {
            delete left;
            delete right;
        }
};

class Tree {
public:
    Tree() :
            root(nullptr)
    { }

    ~Tree() {
        delete root;
    }

    AVLNode* find_diapason(string start, string end);
    AVLNode* find(string key);
    void create(int count);
    void demo(int count);
    void benchmark();
    void display();
    void insert(string value);
    bool empty();

private:
    // Helpers
    static int GetHeight(AVLNode* root);
    static int Diff(AVLNode* root);

    // Rotations
    static AVLNode* RightRight_Rotation(AVLNode* root);
    static AVLNode* LeftLeft_Rotation(AVLNode* root);
    static AVLNode* LeftRight_Rotation(AVLNode* root);
    static AVLNode* RightLeft_Rotation(AVLNode* root);

    // Core
    static AVLNode* BalanceImpl(AVLNode* root);
    static AVLNode* InsertImpl(AVLNode* root, string value);
    static void DisplayImpl(AVLNode* root, int level);

private:
    AVLNode* root;
};


int Tree::GetHeight(AVLNode* temp) {
    int h = 0;
    if (temp) {
        int l_GetHeight = GetHeight(temp->left);
        int r_GetHeight = GetHeight(temp->right);
        int max_GetHeight = std::max(l_GetHeight, r_GetHeight);
        h = max_GetHeight + 1;
    }

    return h;
}

int Tree::Diff(AVLNode* temp) {
    int l_GetHeight = GetHeight(temp->left);
    int r_GetHeight = GetHeight(temp->right);
    int b_factor = (l_GetHeight - r_GetHeight);
    return b_factor;
}

AVLNode* Tree::RightRight_Rotation(AVLNode* parent) {
    AVLNode* temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

AVLNode* Tree::LeftLeft_Rotation(AVLNode* parent) {
    AVLNode* temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

AVLNode* Tree::LeftRight_Rotation(AVLNode* parent) {
    AVLNode* temp = parent->left;
    parent->left = RightRight_Rotation(temp);
    return LeftLeft_Rotation(parent);
}

AVLNode* Tree::RightLeft_Rotation(AVLNode* parent) {
    AVLNode* temp = parent->right;
    parent->right = LeftLeft_Rotation(temp);
    return RightRight_Rotation(parent);
}

AVLNode* Tree::BalanceImpl(AVLNode* temp) {
    int balanceFactor = Diff(temp);

    if (balanceFactor > 1) {
        if (Diff (temp->left) > 0) {
            temp = LeftLeft_Rotation(temp);
        } else {
            temp = LeftRight_Rotation(temp);
        }
    } else if (balanceFactor < -1) {
        if (Diff(temp->right) > 0) {
            temp = RightLeft_Rotation(temp);
        } else {
            temp = RightRight_Rotation(temp);
        }
    }

    return temp;
}

AVLNode* Tree::InsertImpl(AVLNode* root, string value) {
    if (!root) {
        root = new AVLNode{value, nullptr, nullptr};
        return root;
    } else if (value < root->data) {
        root->left = InsertImpl(root->left, value);
        root = BalanceImpl(root);
    } else if (value >= root->data) {
        root->right = InsertImpl(root->right, value);
        root = BalanceImpl(root);
    }

    return root;
}

AVLNode* Tree::find(string key) {
    AVLNode* root_ =  root;
    while(root_) {
        if(root_->data == key) {
            return root_;
        }
        if(root_->data < key) {
            root_ = root_->right;
        }
        else {
            if (root_->data > key) {
                root_ = root_->left;
            }
        }
    }
    return nullptr;
}


AVLNode* Tree::find_diapason(string start, string end) {
    AVLNode* root_ = root;
    while(root_) {
        if(start <= root_->data && root->data <= end) {
            return root_;
        }
        if(root_->data < end) {
            root_ = root_->right;
        }
        else {
            if (root_->data > start) {
                root_ = root_->left;
            }
        }
    }
    return nullptr;
}


void Tree::DisplayImpl(AVLNode* current, int level = 2) {
    if (!current)
        return;

    DisplayImpl(current->left, level + 2);
    std::cout << std::setw(level) << std::setfill('-') << current->data << std::endl;
    DisplayImpl(current->right, level + 2);
}

void Tree::display() {
    DisplayImpl(root);
}

void Tree::insert(string value) {
    root = InsertImpl(root, value);
}

bool Tree::empty() {
    return root == nullptr;
}


void Tree::create(int count) {
    string word;
    for(int i = 0; i < count; i++) {
        int rand = rand_num(RAND) + 1;
        word = "";
        for(int j = 0; j < rand; j++)
            word += char(65 + rand_num(rand) + 1);
        insert(word);
    }
}

void Tree::demo(int count) {
    create(count);
    cout << "created random avl tree" << endl;
    display();
    cout << "finded 1/4 elements" << endl;
    for(int i = 0; i < count / 4; i++)
        find(root->data);
    display();
}

void Tree::benchmark() {
    int N = 6;
    using namespace std::chrono;
    duration<double> time_span;
    float t;
    do {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        create(N);

        for(int i = 0; i < N / 4; i++)
            find(root->data);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        time_span = duration_cast<duration<double>>(t2 - t1);
        t = time_span.count();
        N = N * 2;
    }

    while(t < 5);
    print_memory();
    cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
    cout << "N = " << N << "\n";
}

//task 5


class TwoThreeNode {
private:

    string getSmallest() {
        TwoThreeNode *node = this;
        while (!node->isLeaf()) node = node->child[0];
        return node->key[0];
    }


    void insert1Siblings(TwoThreeNode *newChild, string newSmallest) {
        string newKey = newChild->key[0];
        newChild->parent = this;

        if (newKey < child[0]->key[0]) {

            child[1] = child[0];
            child[0] = newChild;
            key[0] = child[1]->getSmallest();
        }
        else {

            child[1] = newChild;
            key[0] = newSmallest;
        }
    }


    void insert2Siblings(TwoThreeNode *newChild, string newSmallest) {
        string newKey = newChild->key[0];
        newChild->parent = this;

        if (newKey < child[0]->key[0]) {
            child[2] = child[1];
            child[1] = child[0];
            child[0] = newChild;

            key[1] = key[0];
            key[0] = child[1]->getSmallest();
            updateParentSmallest(newSmallest);
        }
        else if (newKey < child[1]->key[0]) {
            child[2] = child[1];
            child[1] = newChild;

            key[1] = key[0];
            key[0] = newSmallest;
        }
        else {
            child[2] = newChild;

            key[1] = newSmallest;
        }
    }

    void insert3Siblings(TwoThreeNode *newChild, string newSmallest) {
        string newKey = newChild->key[0];

        string splitSmallest = "";
        TwoThreeNode *splitNode = new TwoThreeNode();
        splitNode->parent = parent;

        if (newKey < child[0]->key[0] || newKey < child[1]->key[0]) {

            splitSmallest = key[0];
            splitNode->child[0] = child[1];
            splitNode->child[1] = child[2];
            splitNode->key[0] = key[1];

            child[1]->parent = splitNode;
            child[2]->parent = splitNode;
            newChild->parent = this;

            if (newKey < child[0]->key[0]) {

                child[1] = child[0];
                child[0] = newChild;

                key[0] = child[1]->getSmallest();
                updateParentSmallest(newSmallest);
            }
            else {

                child[1] = newChild;

                key[0] = newSmallest;
            }
        }
        else {

            child[2]->parent = splitNode;
            newChild->parent = splitNode;

            if (newKey < child[2]->key[0]) {

                splitSmallest = newSmallest;
                splitNode->child[0] = newChild;
                splitNode->child[1] = child[2];
                splitNode->key[0] = key[1];
            }
            else {

                splitSmallest = key[1];
                splitNode->child[0] = child[2];
                splitNode->child[1] = newChild;
                splitNode->key[0] = newSmallest;
            }
        }

        child[2] = NULL;
        key[1] = -1;

        if (parent->parent == NULL) {

            TwoThreeNode *newNode = new TwoThreeNode();

            parent->child[0] = newNode;
            newNode->parent = parent;
            newNode->child[0] = this;
            parent = newNode;
        }

        parent->insert(splitNode, splitSmallest);
    }


    void updateParentSmallest(string data) {
        switch (sibNumber()) {
            case 0: if (parent->parent != NULL) parent->updateParentSmallest(data); break;
            case 1: parent->key[0] = data; break;
            case 2: parent->key[1] = data; break;
        }
    }

public:
    string key[2];
    TwoThreeNode *parent, *child[3];


    TwoThreeNode(string data = "") {
        key[0] = data;
        key[1] = "";
        parent = child[0] = child[1] = child[2] = NULL;
    }

    bool isLeaf() {
        return (child[0] == NULL);
    }


    int sibNumber() {
        for (int i = 0; i < 3; ++i) {
            if (this == parent->child[i]) return i;
        }
        return -1;
    }


    void insert(TwoThreeNode *newChild, string newSmallest) {
        if (child[1] == NULL) insert1Siblings(newChild, newSmallest);
        else if (child[2] == NULL) insert2Siblings(newChild, newSmallest);
        else insert3Siblings(newChild, newSmallest);
    }
};


class TwoThreeTree {
private:

    void print(TwoThreeNode *node, int tabs = 0) {
        for (int i = 0; i < tabs; ++i) {
            cout << "\t";
        }

        if (node == NULL) {
            cout << "`--> NULL" << endl;
            return;
        }

        cout << "`--> " << node->sibNumber()
             << ": ( " << node->key[0] << ", " << node->key[1] << ")" << endl;

        if (!node->isLeaf()) {
            ++tabs;
            print(node->child[0], tabs);
            print(node->child[1], tabs);
            print(node->child[2], tabs);
        }
    }

public:
    TwoThreeNode *root;


    TwoThreeNode* findSpot(TwoThreeNode *node, string data) {
        if (node == NULL) return NULL;

        while (!node->isLeaf()) {
            if (node->key[0] == data || node->key[1] == data)
                return NULL;
            if (node->key[0] == "" || data < node->key[0])
                node = node->child[0];
            else if (node->key[1] == "" || data < node->key[1])
                node = node->child[1];
            else
                node = node->child[2];
        }

        if (node->key[0] == data) return NULL;
        return node->parent;
    }


    TwoThreeNode* findSpot_diapason(TwoThreeNode *node, string start, string end) {
        if (node == NULL) return NULL;

        while (!node->isLeaf()) {
            if ((start <= node->key[0] && node->key[0] <= end) || (start <= node->key[1] && node->key[1] <= end))
                return NULL;
            if (node->key[0] == "" || end < node->key[0])
                node = node->child[0];
            else if (node->key[1] == "" || end < node->key[1])
                node = node->child[1];
            else
                node = node->child[2];
        }

        if (start <= node->key[0] && node->key[0] <= end) return NULL;
        return node->parent;
    }


    TwoThreeTree() {
        root = new TwoThreeNode();
        root->child[0] = new TwoThreeNode();
        root->child[0]->parent = root;
    }


    bool insert(string data) {
        TwoThreeNode *newNode = new TwoThreeNode(data);
        TwoThreeNode *spot = root->child[0];

        if (spot->child[0] == NULL) {

            newNode->parent = spot;
            spot->child[0] = newNode;
        }
        else {
            spot = findSpot(spot, data);
            if (spot == NULL) return false;

            spot->insert(new TwoThreeNode(data), data);
        }

        return true;
    }


    void print() {
        print(root->child[0]);
        cout << endl;
    }


    void create(int count) {
        string word;
        for(int i = 0; i < count; i++) {
            int rand = rand_num(RAND) + 1;
            word = "";
            for(int j = 0; j < rand; j++)
                word += char(65 + rand_num(rand) + 1);
            insert(word);
        }
    }

    void demo(int count) {
        create(count);
        cout << "created random avl tree" << endl;
        print();
        cout << "finded 1/4 elements" << endl;
        for(int i = 0; i < count / 4; i++)
            findSpot(root, root->key[0]);
    }

    void benchmark() {
        int N = 6;
        using namespace std::chrono;
        duration<double> time_span;
        float t;
        do {
            high_resolution_clock::time_point t1 = high_resolution_clock::now();

            create(N);

            for(int i = 0; i < N / 4; i++)
                findSpot(root, root->key[0]);

            high_resolution_clock::time_point t2 = high_resolution_clock::now();

            time_span = duration_cast<duration<double>>(t2 - t1);
            t = time_span.count();
            N = N * 2;
        }

        while(t < 5);
        print_memory();
        cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
        cout << "N = " << N << "\n";
    }
};



int main() {

    bool created = false;

    LinkedList* list;
    ArrayList* arr;
    BinTree* bin;
    Tree avl;
    TwoThreeTree TTTree;


    string data;
    string second;
    Node* finded_linked;
    int finded_array;
    BinNode* finded_bin;
    AVLNode* finded_avl;
    TwoThreeNode* finded_ttt;
    int count;

    int choice = 0;
    int type = 0;

    cout << "Enter your type: " << endl;
    cout << "1: Linked list" << endl;
    cout << "2: Array list" << endl;
    cout << "3: Binary tree" << endl;
    cout << "4: AVL tree" << endl;
    cout << "5: TwoThree tree" << endl;
    cout << "6: Exit" << endl;

    cin >> type;

    while (true) {

        // Prompt for user input
        cout << "Enter your choice: " << endl;
        cout << "1: create empty list" << endl;
        cout << "2: add element to list" << endl;
        cout << "3: delete element from list" << endl;
        cout << "4: find element by value" << endl;
        cout << "5: find element by diapason" << endl;
        cout << "6: print elements in order" << endl;
        cout << "7: create random list" << endl;
        cout << "8: demonstration" << endl;
        cout << "9: benchmark" << endl;
        cout << "10: exit" << endl;

        cin >> choice;

        switch(type) {
            case 1:
                switch(choice) {
                    case 1:
                        list = create_linked_list();
                        created = true;
                        break;
                    case 2:
                        if(!created) {
                            cout << "create array list at first!" << endl;
                            break;
                        }
                        cout << "enter data to add" << endl;
                        cin >> data;
                        add_element_linked_list(list, data);
                        break;

                    case 3:
                        if(!created) {
                            cout << "create array list at first!" << endl;
                            break;
                        }
                        cout << "enter data to delete" << endl;
                        cin >> data;
                        delete_element_linked_list(list, data);
                        break;

                    case 4:
                        if(!created) {
                            cout << "create array list at first!" << endl;
                            break;
                        }
                        cout << "enter data to find" << endl;
                        cin >> data;
                        finded_linked = find_element_linked_list(list, data);
                        if(!finded_linked)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_linked->data << endl;
                        break;

                    case 5:
                        if(!created) {
                            cout << "create array list at first!" << endl;
                            break;
                        }
                        cout << "enter diapason start to find" << endl;
                        cin >> data;
                        cout << "enter diapason end to find" << endl;
                        cin >> second;
                        finded_linked = find_element_diapason_linked_list(list, data, second);
                        if(!finded_linked)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_linked->data << endl;
                        break;

                    case 6:
                        if(!created) {
                            cout << "create array list at first!" << endl;
                            break;
                        }
                        cout << "Linked List:" << endl;
                        print_linked_list(list);
                        break;

                    case 7:
                        cout << "enter number of random elements: " << endl;
                        cin >> count;
                        list = create_random_linked_list(count);
                        created = true;
                        break;

                    case 8:
                        cout << "enter count of elements" << endl;
                        cin >> count;
                        demo_linked_list(count);
                        created = true;
                        break;

                    case 9:
                        cout << "in process.." << endl;
                        benchmark_linked_list();
                        break;

                    case 10:
                        exit(1);
                        break;

                    default:
                        std::cout << "Wrong choice, please try again." << std::endl;
                }
                break;

            case 2:
                switch(choice) {
                    case 1:
                        arr = create_array_list();
                        created = true;
                        break;
                    case 2:
                        if(!created) {
                            cout << "create array arr at first!" << endl;
                            break;
                        }
                        cout << "enter data to add" << endl;
                        cin >> data;
                        add_element_array_list(arr, data);
                        break;

                    case 3:
                        if(!created) {
                            cout << "create array arr at first!" << endl;
                            break;
                        }
                        cout << "enter data to delete" << endl;
                        cin >> data;
                        delete_element_array_list(arr, data);
                        break;

                    case 4:
                        if(!created) {
                            cout << "create array arr at first!" << endl;
                            break;
                        }
                        cout << "enter data to find" << endl;
                        cin >> data;
                        finded_array = find_element_array_list(arr, data);
                        if(!finded_array)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << arr->arr[finded_array] << endl;
                        break;

                    case 5:
                        if(!created) {
                            cout << "create array arr at first!" << endl;
                            break;
                        }
                        cout << "enter diapason start to find" << endl;
                        cin >> data;
                        cout << "enter diapason end to find" << endl;
                        cin >> second;
                        finded_array = find_element_diapason_array_list(arr, data, second);
                        if(!finded_array)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << arr->arr[finded_array] << endl;
                        break;

                    case 6:
                        if(!created) {
                            cout << "create array arr at first!" << endl;
                            break;
                        }
                        cout << "Array List:" << endl;
                        print_array_list(arr);
                        break;

                    case 7:
                        cout << "enter number of random elements: " << endl;
                        cin >> count;
                        arr = create_random_array_list(count);
                        created = true;
                        break;

                    case 8:
                        cout << "enter count of elements" << endl;
                        cin >> count;
                        demo_array_list(count);
                        created = true;
                        break;

                    case 9:
                        cout << "in process.." << endl;
                        benchmark_array_list();
                        break;

                    case 10:
                        exit(2);
                        break;

                    default:
                        std::cout << "Wrong choice, please try again." << std::endl;
                }
                break;

            case 3:
                switch(choice) {
                    case 1:
                        bin = create_bin_tree();
                        created = true;
                        break;
                    case 2:
                        if(!created) {
                            cout << "create array bin at first!" << endl;
                            break;
                        }
                        cout << "enter data to add" << endl;
                        cin >> data;
                        add_element_bin_tree(bin, data);
                        break;

                    case 3:
                        if(!created) {
                            cout << "create array bin at first!" << endl;
                            break;
                        }
                        cout << "enter data to delete" << endl;
                        cin >> data;
                        delete_element_bin_tree(bin, data);
                        break;

                    case 4:
                        if(!created) {
                            cout << "create array bin at first!" << endl;
                            break;
                        }
                        cout << "enter data to find" << endl;
                        cin >> data;
                        finded_bin = find_element_bin_tree(bin, data);
                        if(!finded_bin)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_bin->data << endl;
                        break;

                    case 5:
                        if(!created) {
                            cout << "create array bin at first!" << endl;
                            break;
                        }
                        cout << "enter diapason start to find" << endl;
                        cin >> data;
                        cout << "enter diapason end to find" << endl;
                        cin >> second;
                        finded_bin = find_element_diapason_bin_tree(bin, data, second);
                        if(!finded_bin)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_bin->data << endl;
                        break;

                    case 6:
                        if(!created) {
                            cout << "create array bin at first!" << endl;
                            break;
                        }
                        cout << "Bin Tree:" << endl;
                        print_bin_tree(bin);
                        break;

                    case 7:
                        cout << "enter number of random elements: " << endl;
                        cin >> count;
                        bin = create_random_bin_tree(count);
                        created = true;
                        break;

                    case 8:
                        cout << "enter count of elements" << endl;
                        cin >> count;
                        demo_bin_tree(count);
                        created = true;
                        break;

                    case 9:
                        cout << "in process.." << endl;
                        benchmark_bin_tree();
                        break;

                    case 10:
                        exit(3);
                        break;

                    default:
                        std::cout << "Wrong choice, please try again." << std::endl;
                }
                break;

            case 4:
                switch(choice) {
                    case 1: {
                        created = true;
                    }
                    case 2: {
                        std::cout << "Enter value to be added: ";
                        std::cin >> data;
                        avl.insert(data);
                        break;
                    }

                    case 3: {
                        cout << "here no delete!" << endl;
                        break;
                    }

                    case 4: {
                        std::cout << "Enter value to be finded: ";
                        std::cin >> data;
                        finded_avl = avl.find(data);
                        if(!finded_avl)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_avl->data << endl;
                        break;
                    }

                    case 5: {
                        cout << "enter diapason start to find" << endl;
                        cin >> data;
                        cout << "enter diapason end to find" << endl;
                        cin >> second;
                        finded_avl = avl.find_diapason(data, second);
                        if(!finded_avl)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_avl->data << endl;
                        break;
                    }

                    case 6: {
                        if (avl.empty()) {
                            cout << "Tree is empty!" << endl;
                        } else {
                            cout << "Balanced AVL Tree:" << endl;
                            avl.display();
                            cout << std::endl;
                        }
                        break;
                    }

                    case 7:
                        cout << "enter number of random elements: " << endl;
                        cin >> count;
                        avl.create(count);
                        created = true;
                        break;

                    case 8:
                        cout << "enter count of elements: " << endl;
                        cin >> count;
                        avl.demo(count);
                        created = true;
                        break;

                    case 9:
                        avl.benchmark();
                        break;

                    case 10: {
                        exit(0);
                        break;
                    }

                    default:
                        std::cout << "Wrong choice, please try again." << std::endl;
                }
                break;

            case 5:

                switch(choice) {
                    case 1: {
                        created = true;
                    }
                    case 2: {
                        std::cout << "Enter value to be added: ";
                        std::cin >> data;
                        TTTree.insert(data);
                        break;
                    }

                    case 3: {
                        cout << "here no delete!" << endl;
                        break;
                    }

                    case 4: {
                        std::cout << "Enter value to be finded: ";
                        std::cin >> data;
                        finded_ttt = TTTree.findSpot(TTTree.root, data);
                        if(!finded_ttt)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_ttt->key[0] << endl;
                        break;
                    }

                    case 5: {
                        cout << "enter diapason start to find" << endl;
                        cin >> data;
                        cout << "enter diapason end to find" << endl;
                        cin >> second;
                        finded_ttt = TTTree.findSpot_diapason(TTTree.root,data, second);
                        if(!finded_ttt)
                            cout << "No such an element in the tree!" << endl;
                        else
                            cout << "This is data from finded element: " << finded_ttt->key[0] << endl;
                        break;
                    }

                    case 6: {
                        cout << "TwoThreeTree: " << endl;
                        TTTree.print();
                        break;
                    }

                    case 7:
                        cout << "enter number of random elements: " << endl;
                        cin >> count;
                        TTTree.create(count);
                        created = true;
                        break;

                    case 8:
                        cout << "enter count of elements: " << endl;
                        cin >> count;
                        TTTree.demo(count);
                        created = true;
                        break;

                    case 9:
                        TTTree.benchmark();
                        break;

                    case 10: {
                        exit(0);
                        break;
                    }

                    default:
                        std::cout << "Wrong choice, please try again." << std::endl;
                }
                break;

            case 6:

                exit(0);
                break;

            default:
                std::cout << "Wrong choice, please try again." << std::endl;
        }
    }

    return 0;
}