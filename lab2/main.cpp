#include <bits/stdc++.h>

using namespace std;

struct rectangle{
    float x1; // х coordinate of top-left angle
    float y1;
    float x2; // х coordinate of right-down angle
    float y2;
    rectangle* next; //
};

// First part (arrays)

const int MAX_SIZE = 10000;

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
        for (int i = index; i < rectangles->size(); i++)
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


// Third part (List)

Spysok* create_empty_list() {
    Spysok* spysok = new Spysok;
    spysok->length = 0;
    spysok-> root = nullptr;
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
    rectangle *rect;
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


int main() {

    cout << "\n" << "First part(array)" << "\n";

    List* lst = create_empty_arr();

    append_arr(lst, 1, 0.5, 1, 1);
    append_arr(lst, 1, 1, 1, 1);
    append_arr(lst, 0, 1, 1, 0);

    insert_arr(lst, 1, 2, 2, 1, 1);
    print_all_arr(lst);

    remove_arr(lst, 2);
    print_all_arr(lst);

    rectangle* ptr_arr = set_arr(lst, 0);
    cout << "This is y1 from this rectangle: " << ptr_arr->y1 << "\n";
    cout << "This is list length: " << length_arr(lst) << "\n";





    cout << "\n" << "Second part(vector)" << "\n";

    vector<rectangle>* rectangles = create_empty_vector();

    append_vector(rectangles, 1, 0.5, 1, 1);
    append_vector(rectangles, 1, 1, 1, 1);
    append_vector(rectangles, 0, 1, 1, 0);

    insert_vector(rectangles, 1, 2, 2, 1, 1);
    print_all_vector(rectangles);

    remove_vector(rectangles, 2);
    print_all_vector(rectangles);

    rectangle* ptr_vector = set_vector(rectangles, 0);
    cout << "This is y1 from this rectangle: " << ptr_vector->y1 << "\n";
    cout << "This is list length: " << length_vector(rectangles) << "\n";
    return 0;
}