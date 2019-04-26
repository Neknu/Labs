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


/* Function to sort an array using insertion sort*/
void insertion_sort(string arr[], int n)
{
    int i, j;
    string key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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
    int count = rand_num(20);
    cout << count;
    random_words(arr, count);
    insertion_sort(arr, count);
    print_array(arr, count);

    return 0;
}
