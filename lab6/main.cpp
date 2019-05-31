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

int const RAND = 20;
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

        for(int i = 0; i < N / 2; i ++)
            delete_element_bin_tree(bin, bin->root->data);

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        time_span = duration_cast<duration<double>>(t2 - t1);
        t = time_span.count();
        N = N * 2;
    }

    while(t < 5);
    cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
    cout << "N = " << N << "\n";
}


//task 4


int main() {

    bool created = false;

    LinkedList* list;
    ArrayList* arr;
    BinTree* bin;

    string data;
    string second;
    Node* finded_linked;
    int finded_array;
    BinNode* finded_bin;
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
                        cout << "Array2 List:" << endl;
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


            case 5:


            case 6:


            default:
                std::cout << "Wrong choice, please try again." << std::endl;
        }
    }

    return 0;
}