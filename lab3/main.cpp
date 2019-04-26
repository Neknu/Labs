#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include <iterator>

using std::string;
using std::cout;
using std::cin;
using std::endl;

const int LENGTH = 10;
string arr[1000000];


int rand_num(double max) {
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

        while (j >= low && arr[j] > key) {
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



void merge(string arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;


    string L[n1], R[n2];


    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];


    i = 0; // Initial index of first array
    j = 0; // Initial index of second array
    k = l;// Initial index of merged array
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(string arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l+r)/2;
        
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}



void combine_sort(string arr[], int l, int r, int edge) {
    if(r-l > edge) {
        int m = (l+r)/2;

        combine_sort(arr, l, m, edge);
        combine_sort(arr, m+1, r, edge);

        merge(arr, l, m, r);
    }
    else {
        insertion_sort(arr, l, r);
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
    int count = rand_num(100);
    cout << count << "\n";
    random_words(arr, count);
    //insertion_sort(arr, 0, count - 1);
    //quick_sort(arr, 0, count - 1);
    //merge_sort(arr, 0, count - 1);
    //combine_sort(arr, 0, count - 1, 10);
    std::sort(arr, arr + count);
    print_array(arr, count);
    return 0;
}
