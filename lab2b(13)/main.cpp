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
        if(lst->root)
            curr->next = lst->root;
        else
            curr->next = curr;
        lst->root = curr;
    }
    else
    if(index == lst->length) {
        Node* prev = set(lst, index - 1);
        Node* curr = new Node;
        curr->data = data;
        curr->next = lst->root;
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

List* remove(List* lst, int data){
    if(lst->root->data == data){
        Node* curr = lst->root;
        while(curr->next != lst->root)
            curr = curr->next;
        curr->next = lst->root->next;
        Node* del = lst->root;
        lst->root = del->next;
        delete(del);
    }
    else {
        Node* curr = lst->root;
        while(curr->next->data != data)
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
    cout << "start - to start console working \n";
    cout << "demo - for demonstration \n";
    cout << "exit - leaves the program( \n";
}

int main() {
    string operation;
    Node* curr;
    List* lst = create_empty();
    while(true) {
        cout_operations();
        cin >> operation;
        if(operation == "start") {
            List* lst = create_empty();
            cout << "Select N - \n";
            int N;
            cin >> N;
            cout << "add N elements to the circle \n";
            for(int i = 0; i < N; i ++) {
                insert(lst, i, i + 1);
            }

            print_all(lst);
            cout << "Select global step - \n";
            int step;
            cin >> step;

            cout << "Select data for deleting - \n";
            int data;
            cin >> data;
            int data_search;

            cout << "Select searching step - \n";
            int search;
            cin >> search;
            int search_search;

            int length = lst->length;
            if(step == 1) {
                for(int i = 0; i < length; i++) {
                    cout << (i + 1) << " ";
                    remove(lst, i + 1);
                }
                cout << "\n";
                cout << "step is :" << data << "\n";
                cout << "data is :" << search << "\n";
            }
            else {
                Node* curr = new Node;
                curr->next = lst->root;

            cout << "List of deleted elements \n";
            for(int i = 0; i < length; i++) {
                for(int j = 0; j < step - 1; j++) {
                    curr = curr->next;
                }
                if(curr->next->data == data) {
                    data_search = i + 1;
                }
                if((i+1) == search) {
                    search_search = curr->next->data;
                }
                cout << curr->next->data << " ";
                remove(lst, curr->next->data);

            }
                cout << "\n";
                cout << "step is :" << data_search << "\n";
                cout << "data is :" << search_search << "\n";
            }
        }
        if(operation == "demo") {
            List* lst = create_empty();
            int N = 5;
            cout << "add 5 elements to the circle \n";
            for(int i = 0; i < N; i ++) {
                insert(lst, i, i + 1);
            }
            print_all(lst);
            cout << "delete list with step 2, also searching step for data 1, data for step 4 \n";
            int step = 2;

            int data = 1;
            int data_search;

            int search = 4;
            int search_search;

            int length = lst->length;
                Node *curr = new Node;
                curr->next = lst->root;
                cout << "List of deleted elements \n";
                for(int i = 0; i < length; i++) {
                    for(int j = 0; j < step - 1; j++) {
                        curr = curr->next;
                    }
                    if(curr->next->data == data) {
                        data_search = i + 1;
                    }
                    if((i+1) == search) {
                        search_search = curr->next->data;
                    }
                    cout << curr->next->data << " ";
                    remove(lst, curr->next->data);

                }
                cout << "\n";
                cout << "step is :" << data_search << "\n";
                cout << "data is :" << search_search << "\n";
        }
        if(operation == "exit") {
            return 0;
        }
    }
}