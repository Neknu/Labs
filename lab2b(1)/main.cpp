#include <iostream>
#include <string>

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
    if(index < lst->length && index >= 0) {
        Node *curr = lst->root;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr;
    }
    return nullptr;
}

Node* set(List* lst, int index) {
    return get(lst, index);
}

List* insert(List* lst, int index, int data) {
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
            if(index < 0) index = lst->length + index;
            cout << "\n" << "this is data from node: " << get(lst, index)->data << "\n";
        }
        if(operation == "set") {
            cout << "index - ";
            cin >> index;
            if(index < 0) index = lst->length + index;
            cout << "\n" << "this is data from node: " << set(lst, index)->data << "\n";
        }
        if(operation == "insert") {
            cout << "index - ";
            cin >> index;
            if(index < 0) index = lst->length + index;
            cout << "data - ";
            cin >> data;
            insert(lst, index, data);
        }
        if(operation == "remove") {
            cout << "index - ";
            if(index < 0) index = lst->length + index;
            cin >> data;
            remove(lst, index);
        }
        if(operation == "print") {
            print_all(lst);
        }
        if(operation == "exit") {
            return 0;
        }
    }
}