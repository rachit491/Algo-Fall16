/**
 *	Huffman Codes
 * 	@author Rachit Shrivastava
 *  @email rshriva@ncsu.edu
 *	To read given input file byte by byte and generate huffman codes 
 *  depending on the frequency of the characters
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using std::hex;
using std::dec;

//Node structure for a binary tree
class Node {
public:
	int count;
	int index;
	Node *left;
	Node *right;

	Node(int i, int c, Node* l, Node* r) {
		index = i;
		count = c;
		left = l;
		right = r;
	}
};

//Swap function to swap two nodes
void swap(Node *x, Node *y) {
	int index, count;
	Node *left, *right;

	index = x->index;
	x->index = y->index;
	y->index = index;

	count = x->count;
	x->count = y->count;
	y->count = count;

	//To-check
	left = x->left;
	x->left = y->left;
	y->left = left;

	right = x->right;
	x->right = y->right;
	y->right = right;	
}

//creating min-heap
void minHeapify(vector<Node* > &heap, int i) {
	int c1 = (2 * i) + 1;
    int c2 = c1 + 1;
    int smallest = i;
    int n = heap.size();

    if(c1 < n && heap[c1]->count < heap[smallest]->count) {
        smallest = c1;
    }

    if(c2 < n && heap[c2]->count < heap[smallest]->count) {
        smallest = c2;
    }

    if(smallest != i) {
        swap(heap[i], heap[smallest]);
        minHeapify(heap, smallest);
    }
}

//extract the top-most element from the min-heap
Node* extractMin(vector<Node *> &heap) {
	Node* min = heap.front();
	//remove top
	heap.front() = heap.back();
	heap.pop_back();                                         //reduce the size of array

	minHeapify(heap, 0);

	return min;
}


void buildMinHeap(vector<Node* > &heap) {
	for(int i = heap.size()/2; i >= 0; --i) {
		minHeapify(heap, i);
	}
}

vector<string> codes(257);		//data structure to print the desired output

// Store huffman codes from the root in above defined data structure
void printHuffmanCodes(Node* root, string str) {
    if(!root)
    	return; 	
    
    int i = root->index;
    if(i != -1) {
    	codes[i] = str;
    	/*if(i == 256) {
			cout<<"EOF"<<" "<<str<<endl;			
		}
		else if(i > 32 && i < 127) {
			cout<<"  "<<(char) i<<" "<<str<<endl;
		}
		else if(i < 16)	{
			cout<<" 0"<<hex<<uppercase<<i<<" "<<str<<endl;
		}
		else {
			cout<<" "<<hex<<uppercase<<i<<" "<<str<<endl;
		}*/
    }

    printHuffmanCodes(root->left, str + "0");
    printHuffmanCodes(root->right, str + "1");
}

//Display the desired ouput format
void display() {
	for(int i = 0; i < codes.size(); i++) {
		if(i == 256) {
			cout<<"EOF"<<" "<<codes[i]<<endl;			
		}
		else if(i > 32 && i < 127) {
			cout<<"  "<<(char) i<<" "<<codes[i]<<endl;
		}
		else if(i < 16)	{
			cout<<" 0"<<hex<<uppercase<<i<<" "<<codes[i]<<endl;
		}
		else {
			cout<<" "<<hex<<uppercase<<i<<" "<<codes[i]<<endl;
		}
	}
}

int main() {
	int i, index, counter = 0;
	char c;
	vector<Node *> heap;

	Node *v1, *v2;

	for(i = 0; i <= 256; i++) {	//including EOF 
		heap.push_back(new Node(i, 1, NULL, NULL));
	}

	while(cin.get(c)) {
		index = (int) c;
		heap[index]->count++;
		counter++;
	}

	buildMinHeap(heap);	//creating heap

	while(heap.size() != 1) {
		v1 = extractMin(heap);
		v2 = extractMin(heap);

		heap.push_back(new Node(-1, v1->count+v2->count, v1, v2));
		minHeapify(heap, 0);
	}

	printHuffmanCodes(heap[0], "");

	display();
	
	return 0;
}