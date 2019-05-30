#include <iostream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <functional>
#include <algorithm>

int const V = 1;
int const COUNT = 127;
int const KOL = 40;
int const INF = 1000000000;

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::min;

double rand_num(double max) {
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(-max, max);

    return dist(gen);
}


struct func {
    string name;
    int level;
};

struct element {
    string type;
    int id;
    int count_func;
    func functions[5 + V];
    double rr;
    double mark;

    element* dad;
    element* son;
    element* next; //brother
};

//task one

struct dstnc {
    double distance; //distnce between 2 components
    double first_mark;
    double second_mark;
    dstnc* left;
    dstnc* right;
};

dstnc* newNode(double item) {
    dstnc *temp =  new dstnc;
    temp->distance = item;
    temp->left = temp->right = nullptr;
    return temp;
}

double mark(element* el) {
    double res = 0;
    for(int i = 0; i < el->count_func; i++) {
        res += el->functions[i].level*el->functions[i].level;
    }
    res = pow(res, V + 2*el->rr);
    return res;
}


double dist(element* el, element* other) {
    double res = 0;
    for(int i = 0; i < el->count_func; i++)
        for(int j = 0; j < other->count_func; j++)
            if(el->functions[i].name == other->functions[j].name) {
                res += pow(min(el->functions[i].level, other->functions[j].level), 2);
            }
    res += 1;
    res = pow(res, min(el->rr, other->rr) - 2*V);
    return res;
}

int create_distances(element* components[], struct dstnc* distances[], int count) {
    int k = 0;
    for(int i = 0; i < count; i++)
        for(int j = i + 1; j < count; j++) {
            dstnc* d = new dstnc;
            d->distance = dist(components[i], components[j]);
            d->first_mark = components[i]->mark;
            d->second_mark = components[j]->mark;
            distances[k] = d;
            k++;
        }
    return k;
}

element* create_random_element() {
    element* el = new element;
    el->type = char(75+int(rand_num(10)));
    el->id = int(rand_num(10)) + 10;
    el->count_func = abs(int(rand_num(5+V)));
    for(int i = 0; i < el->count_func; i++) {
        el->functions[i].name =char(75+int(rand_num(5)));
        el->functions[i].level = abs(int(rand_num(1000))) + 1;
    }
    el->rr = abs(rand_num(1));
    el->mark = mark(el);
    return el;
}


void printBinTree(struct dstnc *root, int depth) {
    if (root != nullptr)
    {
        printBinTree(root->left, depth + 1);
        for(int i = 0; i < depth; i++)
            cout << " --";
        cout << root->distance << "\n";
        printBinTree(root->right, depth + 1);
    }
}


dstnc* insert(dstnc* dstnc, double key) {

    if (dstnc == nullptr) return newNode(key);

    if (key < dstnc->distance)
        dstnc->left  = insert(dstnc->left, key);
    else if (key > dstnc->distance)
        dstnc->right = insert(dstnc->right, key);

    return dstnc;
}

dstnc* find(dstnc* dstnc, double key) {
    while(dstnc) {
        if(dstnc->distance == key)
            return dstnc;
        if(dstnc->distance > key)
            dstnc = dstnc->right;
        else
        if(dstnc->distance < key)
            dstnc = dstnc->left;
    }
    return nullptr;
}


dstnc* build_bin_tree(dstnc* distances[], int count_dist) {
    dstnc *root = nullptr;
    root = insert(root, distances[0]->distance);
    for(int i = 0; i < count_dist; i++)
        insert(root, distances[i]->distance);
    printBinTree(root, 1);
    return root;
}

int main() {
    element* components[COUNT + 1];



    //task 4

    dstnc* distances[KOL*KOL + 1];
    for(int i = 0; i < KOL/4; i++) {
       components[i] = create_random_element();
    }
    int count_dist = create_distances(components, distances, KOL/4);
    dstnc* root = build_bin_tree(distances, count_dist);

    dstnc* find_dist = find(root, distances[4]->distance);
    if(find_dist)
        cout << "this is data from finded node - " << find_dist->distance << "\n";
    else
       cout << "this node doesn't exist!" << "\n";

    return 0;
}