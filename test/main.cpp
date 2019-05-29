#include <bits/stdc++.h>

using namespace std;

void Binary_tree_of_search();
struct Tree{
    Tree* father;
    Tree* l_son;
    Tree* r_son;
    int left_son;
    int right_son;
    int data;
};

int main(){
    Binary_tree_of_search();
    return 0;
}

void recurs_add(Tree* start_el, int in_data, Tree* add_son){
    if (start_el->data <= in_data){
        if (start_el->right_son == 1)
            recurs_add(start_el->r_son, in_data, add_son);
        else if (start_el->right_son != 1){
            start_el->r_son = add_son;
            add_son->father = start_el;
            start_el->right_son = 1;
        }
    }
    else if (start_el->data > in_data){
        if (start_el->left_son == 1)
            recurs_add(start_el->l_son, in_data, add_son);
        else if (start_el->left_son != 1){
            start_el->l_son = add_son;
            add_son->father = start_el;
            start_el->left_son = 1;
        }
    }
}
void add_new_el(Tree* start_el, int data_1, int data_2){
    Tree* new_el_1 = new Tree;
    Tree* new_el_2 = new Tree;
    new_el_1->data = data_1;
    new_el_2->data = data_2;
    if (data_2 >= data_1){
        new_el_1->r_son = new_el_2;
        new_el_1->right_son = 1;
        new_el_2->father = new_el_1;
    }
    else if (data_2 < data_1){
        new_el_1->l_son = new_el_2;
        new_el_1->left_son = 1;
        new_el_2->father = new_el_1;
    }
    if (data_1 < start_el->data){
        if (start_el->left_son == 1)
            recurs_add(start_el->l_son, data_1, new_el_1);
        else if (start_el->left_son != 1){
            start_el->left_son = 1;
            start_el->l_son = new_el_1;
            new_el_1->father = start_el;
        }
    }
    else if (new_el_1->data >= start_el->data){
        if (start_el->right_son == 1)
            recurs_add(start_el->r_son, data_1, new_el_1);
        else {
            start_el->right_son = 1;
            start_el->r_son = new_el_1;
            new_el_1->father = start_el;
        }
    }
}
void cout_tree(Tree* start_el, int indent){
    if (start_el->l_son != 0){
        for (int i = 0; i < indent; i++)
            cout << " ";
        cout << "|l:" << start_el->l_son->data << endl;
        if (start_el->l_son->l_son != 0 || start_el->l_son->r_son != 0)
            cout_tree(start_el->l_son, indent+2);
    }
    if (start_el->r_son != 0){
        for (int i = 0; i < indent; i++)
            cout << " ";
        cout << "|r:" << start_el->l_son->data << endl;
        if (start_el->r_son->l_son != 0 || start_el->r_son->r_son != 0)
            cout_tree(start_el->l_son, indent+2);
    }
}
void Binary_tree_of_search(){
    Tree* Boss = new Tree;
    Boss->father = 0;
    Boss->data = rand()%14+4;
    for (int i = 0; i < 8; i++)
        add_new_el(Boss, rand()%20+1, rand()%20+1);
    cout << Boss->data << endl;
    cout_tree(Boss, 2);
}