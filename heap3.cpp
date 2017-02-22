/**
 * Ternary Heap Implementation
 * @author Rachit Shrivastava
 * @email rshriva@ncsu.edu
 *
 * The code firstly inserts the first element into the heap
 * for each element "add v" following I'm calling insertToHeap function
 * which compares the new element with its parent using the formula specified below
 * and if the new element is smaller than the parent it swaps and check the same for its new position, 
 * in order to create Min Heap

 * as soon as "remove" is encountered removeMin is called which extracts the first element of the heap
 * and calls minHeapify in order to maintain the minHeap status of the data structure
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cmath>

using namespace std;

/**
	Here we were asked to make a ternary heap ie. a heap with 3 child nodes, which comes out to be as follows.
	Consider,
		Let i - parent in a ternary heap, Children for i, for a 0 indexed array
			c1 = (3(i+1)-1)-1 = 3i+1
			c2 = (3(i+1))-1 = 3i+2
			c3 = (3(i+1)+1)-1 = 3i+3
    for any node i its corresponding parent is given by Math.floor((i-1)/3), i!=0
*/

//To swap two values pass by reference
void swap(long long int &x, long long int &y) {
    long long int temp = 0;

    temp = x;
    x = y;
    y = temp;
}

//To maintain the min heap status
void minHeapify(vector<long long int> &arr, long long int i, long long int n) {
    long long int c1 = (3 * i) + 1;
    long long int c2 = c1 + 1;
    long long int c3 = c2 + 1;
    long long int smallest = i;

    if(c1 < n && arr[c1] < arr[smallest]) {
        smallest = c1;
    }

    if(c2 < n && arr[c2] < arr[smallest]) {
        smallest = c2;
    }

    if(c3 < n && arr[c3] < arr[smallest]) {
        smallest = c3;
    }

    if(smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, smallest, n);
    }
}

//Extract the minimal element from the heap
int removeMin(vector<long long int> &arr, long long int n) {
	long long int min = arr.front();
	//remove top
	arr.front() = arr.back();
	arr.pop_back();                                         //reduce the size of array

	minHeapify(arr, 0, arr.size());

	return min;
}

//Return the parent index of given child index
long long int parent(long long int i) {
    return (0 > floor((i-1)/3)) ? 0 : floor((i-1)/3);
}

//add an element to heap maintaining the heap status
void insertToHeap(vector<long long int> &arr, long long int index) {
	if(arr[index] < arr[parent(index)]) {
		swap(arr[index], arr[parent(index)]);
	    insertToHeap(arr, parent(index));
	}
}

int main() {
	int x;
	string value, num = "";

	vector<long long int> instructions;

	while(getline(cin, value)) {
		x = value.find("add ");
		if(x == -1) {
			if(value.find("remove") != -1) {
				//Call min heap & diaplay the extrated result
			    if(instructions.size() > 0) {
			         cout<<removeMin(instructions, instructions.size())<<endl;
			    }
			}
		}
		else {
			num = "";
			for(long long int j=x+4; j<value.length(); j++) {
			    num += value[j];
			}
			//add to array
			instructions.push_back(atoll(num.c_str()));
			//make the array to heap considering new input element
			if(instructions.size() > 1)
			    insertToHeap(instructions, instructions.size()-1);
		}    
	}

	return 0;
}

