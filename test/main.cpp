#include <bits/stdc++.h>

//Лабораторна робота 2b Снєговського Влада К18, задача номер 14

using namespace std;

struct List_str {
    int prior;
    char message[50];
    List_str* next;
};

void list_func();

int main() {
    list_func();
    return 0;
}

List_str* add_new_el(List_str* first, int &count_of_el){
    List_str* new_el = new List_str;
    List_str* help_el_next;
    List_str* help_el_prev;
    cout << "Enter message text:";
    cin >> new_el->message;
    cout << "Enter priority:";
    cin >> new_el->prior;

    int help_int = 0;
    if (count_of_el == 0){
        new_el->next = nullptr;
        first = new_el;
        count_of_el++;
    }
    else if (count_of_el == 1){
        first->next = new_el;
        new_el->next = nullptr;
    }
    else{
        help_el_next = first;
        help_el_prev = first;
        while (help_el_next->prior <= new_el->prior){
            help_el_next = help_el_next->next;
            help_int++;
            if (help_int >= 2)
                help_el_prev = help_el_prev->next;
            if (help_el_next->next == nullptr && help_el_next->prior <= new_el->prior){
                help_int = -1;
                break;
            }
        }
        if (help_int == -1){
            help_el_next->next = new_el;
            new_el->next = nullptr;
        }
        else {
            help_el_prev->next = new_el;
            new_el->next = help_el_next;
        }
    }
    return first;
}
void write_list(List_str* first){
    List_str* cout_str;
    cout_str = first;
    do {
        cout << "priority:" << cout_str->prior << endl;
        cout << "message:" << endl;
        cout << cout_str->message << endl;
        cout_str = cout_str->next;
    }while (cout_str != nullptr);
}
void list_func(){
    List_str* first;
    int way = 0, count_of_el = 0;
    bool check_end = false;
    do{
        cout << "If you want to add new element to the list press 1:" << endl;
        cout << "If you want to see the list press 2:" << endl;
        cout << "If you want to exit press 9:" << endl;
        cin >> way;
        if (way == 1){
            first = add_new_el(first, count_of_el);
        }
        else if (way == 2){
            write_list(first);
        }
        else if (way == 9)
            check_end = true;
    }while (check_end == false);

}