#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <functional>
#include <algorithm>


using std::string;
using std::cin;
using std::cout;
using std::endl;

int const RAND = 10;
int const MAX = 1000000;

int rand_num(int max) {
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(0, max);

    return int(dist(gen));
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

int find_element_array_list(ArrayList* arr, string data) {
    for(int i = 0; i < arr->length; i ++) {
        if(arr->arr[i] > data)
            return -1;
        if (arr->arr[i] == data)
            return i;
    }
    return -1;
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
    else if (key == BinNode->data)
        return nullptr;

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






int main() {

    //task 1
//    LinkedList* list = create_random_linked_list(RAND);
//    //LinkedList* list = create_linked_list();
//    add_element_linked_list(list, "ABB");
//    add_element_linked_list(list, "B");
//    delete_element_linked_list(list, "B");
//    print_linked_list(list);


    //task 2
//    ArrayList* arr = create_random_array_list(RAND);
//    //ArrayList* arr = create_array_list();
//    add_element_array_list(arr, "ABB");
//    add_element_array_list(arr, "B");
//    delete_element_array_list(arr, "B");
//    print_array_list(arr);

    BinTree* bin = create_random_bin_tree(RAND);
    add_element_bin_tree(bin, "D");
    print_bin_tree(bin);
    BinNode* curr = find_element_bin_tree(bin, "D");
    if(curr)
        cout << curr->data << "\n";
    else
        cout << "No element!" << "\n";
    delete_element_bin_tree(bin, "D");
    print_bin_tree(bin);

    return 0;
}