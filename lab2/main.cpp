#include <bits/stdc++.h>

//using namespace std;

using std::cin;
using std::cout;
using std::vector;
using std::swap;
using std::string;

struct rectangle{
    float x1; // х coordinate of top-left angle
    float y1;
    float x2; // х coordinate of right-down angle
    float y2;
    rectangle* next; //
};

// First part (arrays)

const int MAX_SIZE = 100000;
const float koef = 1000;
struct List{
    rectangle rectangles[MAX_SIZE];
    int length;
};

struct Spysok{
    rectangle* root;
    int length;
};


List* create_empty_arr() {
    List* res= new List;
    res->length = 0;
    return res;
}

List* add_element_arr(List* lst, int index, float x1, float y1, float x2, float y2) {
    lst->rectangles[index].x1 = x1;
    lst->rectangles[index].y1 = y1;
    lst->rectangles[index].x2 = x2;
    lst->rectangles[index].y2 = y2;
    lst->length++;
    return lst;
}

List* append_arr(List* lst, float x1, float y1, float x2, float y2) {
    int curr_index;
    curr_index = lst->length;
    if(curr_index < MAX_SIZE) {
        add_element_arr(lst, curr_index, x1, y1, x2, y2);
    } else
        cout << "Список переповнений! Елемент не був доданий!";
    return lst;
}

List* insert_arr(List* lst, int index, float x1, float y1, float x2, float y2) {
    if(index < lst->length && index >= 0) {
        if (lst->length < MAX_SIZE) {
            for (int i = lst->length - 1; i >= index; i--)
                swap(lst->rectangles[i], lst->rectangles[i + 1]);
            add_element_arr(lst, index, x1, y1, x2, y2);
        } else
            cout << "Список переповнений! Елемент не був доданий!";
    }
    return lst;

};

List* remove_arr(List* lst, int index) {
    if(index < lst->length && index >= 0) {
        for (int i = index; i < lst->length - 1; i++)
            swap(lst->rectangles[i], lst->rectangles[i + 1]);
        lst->length--;
    }
    return lst;
};

rectangle* get_arr(List* lst, int index){
    rectangle *ptr;
    if(index < lst->length && index >= 0) {
        ptr = &lst->rectangles[index];
    }
    return ptr;
}

rectangle* set_arr(List* lst, int index){
    return get_arr(lst, index);
}

void print_all_arr(List* lst) {
    for(int i = 0; i < lst->length; i++){
        cout << i << "coordinats: x1 - " << lst->rectangles[i].x1 << " y1 - " << lst->rectangles[i].y1 << " x2 - " << lst->rectangles[i].x2 << " y2 - " << lst->rectangles[i].y2 << "\n";
    }
    cout << "\n";
}

int length_arr(List* lst) {
    return lst->length;
}

List* random_append_arr(List* lst ,int count) {
    float x1, x2, y1, y2;
     for(int i = 0; i < count; i++) {
        x1 = (rand() % int(koef)) / koef;
        y1 = (rand() % int(koef)) / koef;
        x2 = (rand() % int(koef)) / koef;
        y2 = (rand() % int(koef)) / koef;
        append_arr(lst, x1, y1, x2, y2);
    }
    return lst;
}

List* random_delete_arr(List* lst ,int count) {
    float x1, x2, y1, y2;
    for(int i = 0; i < count; i++) {
        remove_arr(lst, i);
    }
    return lst;
}

// Second part (vector)

vector<rectangle>* create_empty_vector() {
    vector<rectangle>* vec = new vector<rectangle>;
    return vec;
}

rectangle add_element_vec(float x1, float y1, float x2, float y2) {
    rectangle rect;
    rect.x1 = x1;
    rect.y1 = y1;
    rect.x2 = x2;
    rect.y2 = y2;
    return rect;
}

vector<rectangle>* append_vector(vector<rectangle>* rectangles, float x1, float y1, float x2, float y2) {
        rectangle rect = add_element_vec(x1, y1, x2, y2);
        rectangles->push_back(rect);
    return rectangles;
}

vector<rectangle>* insert_vector(vector<rectangle>* rectangles, int index, float x1, float y1, float x2, float y2) {
    if(index < rectangles->size() && index >= 0) {
        rectangle rect = add_element_vec(x1, y1, x2, y2);
        rectangles->push_back(rect);
        for (int i = rectangles->size() - 2; i >= index; i--)
            swap((*rectangles)[i], (*rectangles)[i + 1]);
    }
    return rectangles;
};

vector<rectangle>* remove_vector(vector<rectangle>* rectangles, int index) {
    if(index < rectangles->size() && index >= 0) {
        for (int i = index; i < rectangles->size() - 1; i++)
            swap((*rectangles)[i], (*rectangles)[i + 1]);
        rectangles->pop_back();
    }
    return rectangles;
};

rectangle* get_vector(vector<rectangle>* rectangles, int index){
    rectangle *rect;
    if(index < rectangles->size() && index >= 0) {
        rect = &(*rectangles)[index];
    }
    return rect;
}

rectangle* set_vector(vector<rectangle>* rectangles, int index){
    return get_vector(rectangles, index);
}

void print_all_vector(vector<rectangle>* rectangles) {
    for(int i = 0; i < rectangles->size(); i++){
        cout << i << "coordinats: x1 - " << (*rectangles)[i].x1 << " y1 - " << (*rectangles)[i].y1 << " x2 - " << (*rectangles)[i].x2 << " y2 - " << (*rectangles)[i].y2 << "\n";
    }
    cout << "\n";
}

int length_vector(vector<rectangle>* rectangles) {
    return rectangles->size();
}

vector<rectangle>* random_append_vector(vector<rectangle>* rectangles ,int count) {
    float x1, x2, y1, y2;
    for(int i = 0; i < count; i++) {
        x1 = (rand() % int(koef)) / koef;
        y1 = (rand() % int(koef)) / koef;
        x2 = (rand() % int(koef)) / koef;
        y2 = (rand() % int(koef)) / koef;
        append_vector(rectangles, x1, y1, x2, y2);
    }
    return rectangles;
}

vector<rectangle>* random_delete_vector(vector<rectangle>* rectangles ,int count) {
    for(int i = 0; i < count; i++) {
        remove_vector(rectangles, i);
    }
    return rectangles;
}


// Third part (List)

Spysok* create_empty_list() {
    Spysok* spysok = new Spysok;
    spysok->length = 0;
    spysok->root = nullptr;
    return spysok;
}

rectangle* add_element_list(rectangle* next, float x1, float y1, float x2, float y2) {
    rectangle* rect = new rectangle;
    rect->x1 = x1;
    rect->y1 = y1;
    rect->x2 = x2;
    rect->y2 = y2;
    rect->next = next;
    return rect;
}

Spysok* append_list(Spysok* spysok, float x1, float y1, float x2, float y2) {
    rectangle* rect;
    if(spysok->length == 0) {
        rect = add_element_list(nullptr, x1, y1, x2, y2);
        spysok->root = rect;
    }
    else {
        rectangle* curr = spysok->root;
        while(curr->next != nullptr)
            curr = curr->next;
        rect = add_element_list(nullptr, x1, y1, x2, y2);
        curr->next = rect;
    }
    spysok->length++;
    return spysok;
}

rectangle* get_list(Spysok* spysok, int index) {
    if(index < spysok->length && index >= 0) {
        rectangle *curr = spysok->root;
        for (int i = 0; i < index; i++)
            curr = curr->next;
        return curr;
    }
    return nullptr;
}

rectangle* set_list(Spysok* spysok, int index) {
    return get_list(spysok, index);
}

Spysok* insert_list(Spysok* spysok, int index, float x1, float y1, float x2, float y2) {
    if(index < spysok->length && index >= 0) {
        rectangle* curr = get_list(spysok, index);
        rectangle* rect = add_element_list(curr->next, curr->x1, curr->y1, curr->x2, curr->y2);
        curr->x1 = x1;
        curr->y1 = y1;
        curr->x2 = x2;
        curr->y2 = y2;
        curr->next = rect;
        spysok->length++;
    }
    else
        cout << "Nothing happend!";
    return spysok;
}

Spysok* remove_list(Spysok* spysok, int index){
    if(index < spysok->length && index >= 0) {
        rectangle *curr = spysok->root;
        for (int i = 0; i < index - 1; i++)
            curr = curr->next;
        rectangle* tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
        spysok->length--;
    }
    return spysok;
}

void print_all_list(Spysok* spysok){
    rectangle* jump = spysok->root;
    for(int i = 0; i < spysok->length; i++) {
        cout << i << "coordinats: x1 - " << jump->x1 << " y1 - " << jump->y1 << " x2 - " << jump->x2 << " y2 - " << jump->y2 << "\n";
        jump = jump->next;
    }
    cout << "\n";
}

int length_list(Spysok* spysok) {
    return spysok->length;
}

Spysok* random_append_list(Spysok* spysok ,int count) {
    float x1, x2, y1, y2;
    for(int i = 0; i < count; i++) {
        x1 = (rand() % int(koef)) / koef;
        y1 = (rand() % int(koef)) / koef;
        x2 = (rand() % int(koef)) / koef;
        y2 = (rand() % int(koef)) / koef;
        append_list(spysok, x1, y1, x2, y2);
    }
    return spysok;
}

Spysok* random_delete_list(Spysok* spysok, int count) {
    for(int i = 0; i < count; i++) {
        remove_list(spysok, i);
    }
    return spysok;
}


void cout_select_type() {
    cout << "Select your type: \n";
    cout << "1 - array \n";
    cout << "2 - vector \n";
    cout << "3 - list \n";
    cout << "4 - exit \n";
}

void cout_operations() {
    cout << "\n";
    cout << "\n";
    cout << "This is operations list: \n";
    cout << "create_empty - create empty list \n";
    cout << "append - add rect to the end \n";
    cout << "insert - add rect after index \n";
    cout << "remove - remove rect with index \n";
    cout << "get - print all coordinats by index \n";
    cout << "set - the same as get \n";
    cout << "length - length of list \n";
    cout << "print - print all elements of list \n";
    cout << "demo - for demonstration(will create new list) \n";
    cout << "benchmark - for calculating time of program working \n";
    cout << "exit - exit to first menu \n";
}



int main() {

    int type;
    string operation;
    List* lst;
    bool create = false;
    vector<rectangle>* rectangles;
    Spysok* spysok;
    float x1, y1, x2, y2;
    int index;

    while (true) {
        if(type != 1 && type != 2 && type != 3 && type != 4) {
            cout_select_type();
            cin >> type;
        }
        switch (type) {
            case 1: {
                cout << "Your type is array! \n";
                cout_operations();
                cin >> operation;
                if(operation == "create_empty") {
                    lst = create_empty_arr();
                    create = true;
                }
                if (operation == "demo") {
                    lst = create_empty_arr();
                    random_append_arr(lst, 6);
                    cout << "6 rectangles was added: \n";
                    print_all_arr(lst);
                    random_delete_arr(lst, 3);
                    cout << "3 rectangles was deleted: \n";
                    print_all_arr(lst);
                    create = true;
                }
                if (operation == "benchmark") {
                    int N = 6;
                    using namespace std::chrono;
                    duration<double> time_span;
                    float t;
                    do {
                        high_resolution_clock::time_point t1 = high_resolution_clock::now();
                        lst = create_empty_arr();
                        // here random
                        random_append_arr(lst, N);
                        // this is very slow function so speed will be low
                        random_delete_arr(lst, N / 2);

                        high_resolution_clock::time_point t2 = high_resolution_clock::now();

                        time_span = duration_cast<duration<double>>(t2 - t1);
                        t = time_span.count();
                        N = N * 2;
                    }
                    while(N * 2 < MAX_SIZE);
                    create = true;
                    cout << "\n" <<  "It took me " << t << " seconds. \n";
                    cout << "N = " << N << "\n";
                }
                if(create) {
                    if (operation == "append") {
                        cout << "x1 - ";
                        cin >> x1;
                        cout << "y1 - ";
                        cin >> y1;
                        cout << "x2 - ";
                        cin >> x2;
                        cout << "y2 - ";
                        cin >> y2;
                        lst = append_arr(lst, x1, y1, x2, y2);
                    }
                    if (operation == "insert") {
                        cout << "index - ";
                        cin >> index;
                        cout << "x1 - ";
                        cin >> x1;
                        cout << "y1 - ";
                        cin >> y1;
                        cout << "x2 - ";
                        cin >> x2;
                        cout << "y2 - ";
                        cin >> y2;
                        lst = insert_arr(lst, index, x1, y1, x2, y2);
                    }
                    if (operation == "remove") {
                        cout << "index - ";
                        cin >> index;
                        lst = remove_arr(lst, index);
                    }
                    if (operation == "get") {
                        cout << "index - ";
                        cin >> index;
                        rectangle *rect = get_arr(lst, index);
                        cout << "this is rectangle: x1 - " << rect->x1 << " y1 - " << rect->y1 << " x2 - " << rect->x2
                             << " y2 - " << rect->y2 << "\n";
                    }
                    if (operation == "set") {
                        cout << "index - ";
                        cin >> index;
                        rectangle *rect = set_arr(lst, index);
                        cout << "this is rectangle: x1 - " << rect->x1 << " y1 - " << rect->y1 << " x2 - " << rect->x2
                             << " y2 - " << rect->y2 << "\n";
                    }
                    if (operation == "length") {
                        cout << "this is length of list: " << length_arr(lst) << "\n";
                    }
                    if (operation == "print") {
                        print_all_arr(lst);
                    }
                    if (operation == "exit") {
                        type = 0;
                        create = false;
                        continue;
                    }
                } else
                   cout << "Create list please! \n";
                break;
            }
            case 2: {
                cout << "Your type is vector! \n";
                cout_operations();
                cin >> operation;
                if(operation == "create_empty") {
                    rectangles = create_empty_vector();
                }
                if (operation == "demo") {
                    rectangles = create_empty_vector();
                    random_append_vector(rectangles, 6);
                    cout << "6 rectangles was added: \n";
                    print_all_vector(rectangles);
                    random_delete_vector(rectangles, 3);
                    cout << "3 rectangles was deleted: \n";
                    print_all_vector(rectangles);
                    create = true;
                }
                if (operation == "benchmark") {
                    int N = 6;
                    using namespace std::chrono;
                    duration<double> time_span;
                    float t;
                    do {
                        high_resolution_clock::time_point t1 = high_resolution_clock::now();
                        rectangles = create_empty_vector();
                        // here random
                        random_append_vector(rectangles, N);
                        // if we comment next stroke speed of program extremely increases, so let try it
                        //random_delete_vector(rectangles, N / 2);

                        high_resolution_clock::time_point t2 = high_resolution_clock::now();

                        time_span = duration_cast<duration<double>>(t2 - t1);
                        t = time_span.count();
                        N = N * 2;
                    }
                    //only 1 s because memory limit
                    while(t < 1);
                    create = true;
                    cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
                    cout << "N = " << N << "\n";
                }
                if(create) {
                    if (operation == "append") {
                        cout << "x1 - ";
                        cin >> x1;
                        cout << "y1 - ";
                        cin >> y1;
                        cout << "x2 - ";
                        cin >> x2;
                        cout << "y2 - ";
                        cin >> y2;
                        append_vector(rectangles, x1, y1, x2, y2);
                    }
                    if (operation == "insert") {
                        cout << "index - ";
                        cin >> index;
                        cout << "x1 - ";
                        cin >> x1;
                        cout << "y1 - ";
                        cin >> y1;
                        cout << "x2 - ";
                        cin >> x2;
                        cout << "y2 - ";
                        cin >> y2;
                        insert_vector(rectangles, index, x1, y1, x2, y2);
                    }
                    if (operation == "remove") {
                        cout << "index - ";
                        cin >> index;
                        remove_vector(rectangles, index);
                    }
                    if (operation == "get") {
                        cout << "index - ";
                        cin >> index;
                        rectangle *rect = get_vector(rectangles, index);
                        cout << "this is rectangle: x1 - " << rect->x1 << " y1 - " << rect->y1 << " x2 - " << rect->x2
                             << " y2 - " << rect->y2 << "\n";
                    }
                    if (operation == "set") {
                        cout << "index - ";
                        cin >> index;
                        rectangle *rect = set_vector(rectangles, index);
                        cout << "this is rectangle: x1 - " << rect->x1 << " y1 - " << rect->y1 << " x2 - " << rect->x2
                             << " y2 - " << rect->y2 << "\n";
                    }
                    if (operation == "length") {
                        cout << "this is length of list: " << length_vector(rectangles) << "\n";
                    }
                    if (operation == "print") {
                        print_all_vector(rectangles);
                    }
                    if (operation == "exit") {
                        type = 0;
                        continue;
                    }
                } else
                   cout << "Create list please! \n";
                break;
            }
            case 3: {
                cout << "Your type is list! \n";
                cout_operations();
                cin >> operation;
                if(operation == "create_empty") {
                    spysok = create_empty_list();
                    create = true;
                }
                if (operation == "demo") {
                    spysok = create_empty_list();
                    random_append_list(spysok, 6);
                    cout << "6 rectangles was added: \n";
                    print_all_list(spysok);
                    random_delete_list(spysok, 3);
                    cout << "3 rectangles was deleted: \n";
                    print_all_list(spysok);
                    create = true;
                }
                if (operation == "benchmark") {
                    int N = 6;
                    using namespace std::chrono;
                    duration<double> time_span;
                    float t;
                    do {
                        high_resolution_clock::time_point t1 = high_resolution_clock::now();
                        spysok = create_empty_list();
                        // here random
                        random_append_list(spysok, N);
                        // here speed of deleting is normal
                        random_delete_list(spysok, N / 2);

                        high_resolution_clock::time_point t2 = high_resolution_clock::now();

                        time_span = duration_cast<duration<double>>(t2 - t1);
                        t = time_span.count();
                        N = N * 2;
                    }
                    while(t < 10);
                    create = true;
                    cout << "\n" <<  "It took me " << time_span.count() << " seconds. \n";
                    cout << "N = " << N << "\n";
                }
                if(create) {
                    if (operation == "append") {
                        cout << "x1 - ";
                        cin >> x1;
                        cout << "y1 - ";
                        cin >> y1;
                        cout << "x2 - ";
                        cin >> x2;
                        cout << "y2 - ";
                        cin >> y2;
                        append_list(spysok, x1, y1, x2, y2);
                    }
                    if (operation == "insert") {
                        cout << "index - ";
                        cin >> index;
                        cout << "x1 - ";
                        cin >> x1;
                        cout << "y1 - ";
                        cin >> y1;
                        cout << "x2 - ";
                        cin >> x2;
                        cout << "y2 - ";
                        cin >> y2;
                        insert_list(spysok, index, x1, y1, x2, y2);
                    }
                    if (operation == "remove") {
                        cout << "index - ";
                        cin >> index;
                        remove_list(spysok, index);
                    }
                    if (operation == "get") {
                        cout << "index - ";
                        cin >> index;
                        rectangle *rect = get_list(spysok, index);
                        cout << "this is rectangle: x1 - " << rect->x1 << " y1 - " << rect->y1 << " x2 - " << rect->x2
                             << " y2 - " << rect->y2 << "\n";
                    }
                    if (operation == "set") {
                        cout << "index - ";
                        cin >> index;
                        rectangle *rect = set_list(spysok, index);
                        cout << "this is rectangle: x1 - " << rect->x1 << " y1 - " << rect->y1 << " x2 - " << rect->x2
                             << " y2 - " << rect->y2 << "\n";
                    }
                    if (operation == "length") {
                        cout << "this is length of list: " << length_list(spysok) << "\n";
                    }
                    if (operation == "print") {
                        print_all_list(spysok);
                    }
                    if (operation == "exit") {
                        type = 0;
                        create = false;
                        continue;
                    }
                } else
                    cout << "Create list please! \n";
                break;
            }
            case 4: {
                return 0;
                break;
            }

            default: {
                cout << "select type (1..3)! \n";
            }
    }
}

}