#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <random>

using std::string;
using std::cout;
using std::cin;
using std::endl;

const int LENGTH = 10;
string arr[LENGTH*5];


int rand_num(int max) {
    static std::random_device rd;
    static std::seed_seq seed { rd(), static_cast<unsigned int>(time(nullptr))};
    static std::mt19937_64 gen(seed);
    std::uniform_real_distribution<double> dist(max/2, max);
    return dist(gen);
}


void insertion_sort(string arr[], int n)
{
    int i, j;
    string key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}




/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(string arr[], int low, int high)
{
    string pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quick_sort(string arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}




// A utility function to print an array of size n
void print_array(string arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout <<  arr[i] << " ";
    cout << "\n";
}

void random_words(string arr[], int n) {
    for (int i = 0; i < n; i++) {
        int kol = rand_num(LENGTH);
        for (int j = 0; j < kol; j++)
            arr[i] += char(rand_num(LENGTH) + 48);

    }
}

/* Driver program to test insertion sort */
int main()
{
    //string arr[] = { "RA", "YB", "ACB", "DBBBBB", "gagagagaga", "hh", "ATT" };
    int count = rand_num(5);
    cout << count << "\n";
    random_words(arr, count);
    //insertion_sort(arr, count);
    quick_sort(arr, 0, count - 1);
    print_array(arr, count);
    return 0;
}
