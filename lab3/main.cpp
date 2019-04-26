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


void insertion_sort(string arr[], int low, int high)
{
    int i, j;
    string key;
    for (i = low + 1; i < high + 1; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}



int partition(string arr[], int low, int high)
{
    string pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}


void quick_sort(string arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}




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
            arr[i] += char(rand_num(LENGTH) + 60); // 60 just for 'A..Z'

    }
}

/* Driver program to test insertion sort */
int main()
{
    //string arr[] = { "RA", "YB", "ACB", "DBBBBB", "gagagagaga", "hh", "ATT" };
    int count = rand_num(20);
    cout << count << "\n";
    random_words(arr, count);
    insertion_sort(arr, 0, count - 1);
//    quick_sort(arr, 0, count - 1);
    print_array(arr, count);
    return 0;
}
