#include <iostream>
#include <string>
#include <chrono>

using std::cout;
using std::cin;
using std::string;

struct Node {
    int data;
    Node* next;
};

struct List{
    Node* root;
    int length;
};

List* create_empty() {
    List* lst = new List;
    lst->length = 0;
    lst->root = nullptr;
    return lst;
}

Node* get(List* lst, int index) {
    if(index < 0) index = lst->length + index;
    if(index < lst->length && index >= 0) {
        Node *curr = lst->root;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr;
    }
    return nullptr;
}

Node* set(List* lst, int index) {
    if(index < 0) index = lst->length + index;
    return get(lst, index);
}

List* insert(List* lst, int index, int data) {
    if(index < 0) index = lst->length + index;
    if(index == 0) {
        Node* curr = new Node;
        curr->data = data;
        curr->next = lst->root;
        lst->root = curr;
    }
    else
    if(index == lst->length) {
        Node* prev = set(lst, index - 1);
        Node* curr = new Node;
        curr->data = data;
        curr->next = nullptr;
        prev->next = curr;
    }
    else
    if(index < lst->length && index > 0) {
        Node* curr = set(lst, index);
        Node* next = new Node;
        next->data = curr->data;
        curr->data = data;
        next->next = curr->next;
        curr->next = next;
    }
    lst->length++;
    return lst;
}

List* remove(List* lst, int index){
    if(index < 0) index = lst->length + index;
    if(index == 0) {
        Node* del = lst->root;
        lst->root = del->next;
        delete(del);
    }
    if(index < lst->length && index > 0) {
        Node *curr = lst->root;
        for (int i = 0; i < index - 1; i++)
            curr = curr->next;
        Node* tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
    }
    lst->length--;
    return lst;
}

void print_all(List* lst){
    Node* jump = lst->root;
    for(int i = 0; i < lst->length; i++) {
        cout << i << " :" << jump->data << "\n";
        jump = jump->next;
    }
    cout << "\n";
}

void cout_operations() {
    cout <<"\n";
    cout << "get - get data by index \n";
    cout << "set - get function get \n";
    cout << "insert - add element by index \n";
    cout << "remove - delete element by index \n";
    cout << "print - print all elements \n";
    cout <<" demo - for demonstration \n";
    cout << "benchmark - for calculating time of program working \n";
    cout << "exit - leaves the program( \n";
}

int main() {
    string operation;
    int data;
    List* lst = create_empty();
    int index;
    while(true) {
        cout_operations();
        cin >> operation;
        if(operation == "get") {
            cout << "index - ";
            cin >> index;
            cout << "\n" << "this is data from node: " << get(lst, index)->data << "\n";
        }
        if(operation == "set") {
            cout << "index - ";
            cin >> index;
            cout << "\n" << "this is data from node: " << set(lst, index)->data << "\n";
        }
        if(operation == "insert") {
            cout << "index - ";
            cin >> index;
            cout << "data - ";
            cin >> data;
            insert(lst, index, data);
        }
        if(operation == "remove") {
            cout << "index - ";
            cin >> data;
            remove(lst, index);
        }
        if(operation == "demo") {
            cout << "adding new elements: \n";
            for(int i = 0; i < 3; i ++) {
                insert(lst, i, i + 1);
            }
            print_all(lst);

            cout << "inserting element by index 0 \n";
            insert(lst, 0, 0);
            print_all(lst);

            cout << "remove element by id -1 \n";
            remove(lst, -1);
            print_all(lst);

            cout << "set element by id -2 \n";
            Node* nd = set(lst, -2);
            cout << "this is data from this node: " << nd->data << "\n";

        }
        if(operation == "benchmark") {
            int N = 6;
            using namespace std::chrono;
            duration<double> time_span;
            float t;
            do {
                List* lst = create_empty();
                high_resolution_clock::time_point t1 = high_resolution_clock::now();
                for(int i = 0; i < N; i ++) {
                    insert(lst, i, i + 1);
                }

                for(int i = 0; i < N / 2; i ++) {
                    remove(lst, i);
                }
                high_resolution_clock::time_point t2 = high_resolution_clock::now();

                time_span = duration_cast<duration<double>>(t2 - t1);
                t = time_span.count();
                N = N * 2;
            }

            while(t < 10);
            cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
            cout << "N = " << N << "\n";

        }
        if(operation == "print") {
            print_all(lst);
        }
        if(operation == "exit") {
            return 0;
        }
    }
}