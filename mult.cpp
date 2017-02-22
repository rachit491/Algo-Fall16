/**
 * Matrix Chain Multiplication
 * @author Rachit Shrivastava
 * @email rshriva@ncsu.edu
 *
 * Uses the logic discussed in class and Algorithms book by Coreman
 * to find out the optimal solution to solve matrix chain multiplication
 */

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

//To display the output as desired
void displaySeq(vector< vector<long long int> > s, int i, int j) {
	int size = s[0].size()-1;

	if(i == j) {
		cout<<"M"<<i;
	}
	else {
		if(i == 1 && j == size) {}
		else{
			cout<<"( ";
		}

		displaySeq(s, i, s[i][j]);
		cout<<" * ";
		displaySeq(s, s[i][j]+1, j);
		
		if(i == 1 && j == size) {}
		else {
			cout<<" )";
		}
	}
}

int main() {
	int i, j, k;				//loop indices
	int n;						//length of input
	long long int temp;
	cin>>n;

	vector<int> p(n+1);		

	for(i = 0; i <= n; i++) {
		cin>>p[i];				//initialize sequence of matrix heights-width
	}

	vector< vector<long long int> > cost;
	vector< vector<long long int> > seq;	//2d vectors to store cost and seq to reach that cost
	
	cost.resize(n+1, vector<long long int>(n+1, 0));
	seq.resize(n+1, vector<long long int>(n+1, 0));

	for(int l = 2; l <= n; l++) {
		for(i = 1; i <= n-l+1; i++) {
			j = i+l-1;
			cost[i][j] = LLONG_MAX;
			for(k = i; k <= j-1; k++) {
				temp = cost[i][k] + cost[k+1][j] + p[i-1]*p[k]*p[j];
				if(temp < cost[i][j]) {
					cost[i][j] = temp;
					seq[i][j] = k;
				}
			}
		}
	}

	displaySeq(seq, 1, n);
	cout<<endl;

	return 0;
}