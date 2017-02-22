/**
 * Quick Sort Base Case Comparison
 * @author Rachit Shrivastava
 * @email rshriva@ncsu.edu
 *
 * The program accepts a k value and elements to be sorted
 * k is level at which the Quick Sort behavior will change to Bubble Sort
 * it also calculates the time to perform the QuickSort/BubbleSort operation on an array of n elements
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#include <string>
#include <ctype.h>

using namespace std;

void swap(long long int &x, long long int &y) {
    long long int temp = 0;

    temp = x;
    x = y;
    y = temp;
}

int partition(vector<long long int> &arr, long long int p, long long int r) {
    long long int i = p-1;

    for(long long int j=p; j<r; j++) {
        if(arr[j] <= arr[r]) {              //Considering pivot as last element in array
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i+1], arr[r]);

    return (i+1);
}

//Bubble sort for k length arrays
void bubbleSort(vector<long long int> &arr, long long int start, long long int end) {
    for(int i = start; i < end; i++) {
        for(int j = start; j < end; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

//Quick Sort implementation with bubble after k length
void quickSort(vector<long long int> &arr, long long int p, long long int r, int k) {
    long long int q;  //Pivot
    if(p < r) {
        q = partition(arr, p, r);
        //Check conditions for Bubble Sort to take over
        if(((q-1)-p) <= k) {
            bubbleSort(arr, p, q-1);
        } else {
            quickSort(arr, p, q-1, k);
        }

        if(r-(q+1) <= k) {
            bubbleSort(arr, q+1, r);
        } else {
            quickSort(arr, q+1, r, k);
        }
    }   
}

//Get current time
long long int getMilliseconds() {
    timeval tv;
    gettimeofday( &tv, NULL );
    long int ms = tv.tv_sec;
    ms = ms * 1000 + tv.tv_usec / 1000;
    return ms;
}

int main(int argc, char** argv) {
    int k;
    string value;
    long long int n = 0, seconds;
    vector<long long int> arr;
    
    //Input k value
    for (int i = 0; i < argc; ++i) {
        if(isdigit(*argv[i])) {
            k = atoi(argv[i]);
        }
    }
    
    //Read the array to be sorted
    while(getline(cin, value)) {
        arr.push_back(atoll(value.c_str()));
        n++;
    }
    
    long long int t0 = getMilliseconds();                              
    quickSort(arr, 0, n-1, k);
    long long int t1 = getMilliseconds();                              

    seconds = t1 - t0;   
    cerr<<seconds<<endl;

    for(long long int i=0; i<n; i++) {
        cout<<arr[i]<<endl;
    }

    return 0;
}
