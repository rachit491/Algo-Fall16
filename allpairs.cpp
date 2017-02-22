/**
 *	All-pairs shortest paths - with extra credit
 * 	@author Rachit Shrivastava
 *  @email rshriva@ncsu.edu
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class Flyod {
	int n;
	vector<string> nodes;		//list of nodes
	vector<string> pairs;		//list for pairs
	vector< vector<int> > adj;	//adjacency matrix
	vector< vector<int> > adjCopy;	//adjacency matrix copy

	vector< vector<int> > q;	//tracking matrix - Extra Credit

	public:
		Flyod(int no) {
			n = no;
			nodes.resize(n);
			adj.resize(n, vector<int> (n));
			adjCopy.resize(n, vector<int> (n));
			q.resize(n, vector<int> (n));
		}

		//reading nodes name
		void inputNodes() {
			for(int i=0; i<n; i++) {
				cin>>nodes[i];
			}
		}

		//reading pairs input
		void inputPairs(int m) {
			pairs.resize(m);
			string dummy;
			getline(cin, dummy);

			for(int i=0; i<m; i++) {
				getline(cin, pairs[i]);
			}
		}

		void outputAverage() {
			/*for(int i=0; i<n; i++) {
				cout<<nodes[i]<<"\n";
			}

			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					if(adj[i][j] == 99999)
						cout<<"-1 ";
					else
						cout<<adj[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"\n";

			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					if(adjCopy[i][j] == 99999)
						cout<<"-1 ";
					else
						cout<<adjCopy[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<"\n";

			cout<<"matrix q: \n";
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					cout<<q[i][j]<<" ";
				}
				cout<<endl;
			}*/

			//average
			int count = 0;
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					if(adj[i][j] != 99999) {
						count++;
					}
				}
			}
			cout<<setprecision(2)<<fixed<<(float)count/n<<endl;
		}

		//mapping node names with their respective indices in order to track in pair
		vector<int> findNodes(string pair) {
			vector<int> v(2);
			int pos;

			for(int i=0; i<n; i++) {
				pos = pair.find(nodes[i]);
				if(pos == 0) {
					v[0] = i;
				}
				if(pos > 0 && pos < n) {
					v[1] = i;
				}
			}
			return v;
		}

		//display the path as desired
		void outputPaths() {
			vector<int> nodesArr;
			for(int i=0; i<pairs.size(); i++) {
				nodesArr = findNodes(pairs[i]);
				if(nodesArr.size() == 2) {
					//means we found these nodes exists from input
					if(adj[nodesArr[0]][nodesArr[1]] != 99999)
						cout<<adj[nodesArr[0]][nodesArr[1]]<<" ";

					cout<<nodes[nodesArr[0]]<<" ";
					
					writePath(nodesArr[0], nodesArr[1]);

					if(adj[nodesArr[0]][nodesArr[1]] == 99999)
						cout<<"not reachable";
					cout<<endl;
				}
				else {
					cout<<pairs[i]<<" not reachable"<<endl;
				}
			}
		}

		void writePath(int i, int j) {
			//print start
			//search direct path
			//if not, search in Q matrix for next nearest
			//change start, writePath again

			if(i == j || i < 0 || j < 0) {
				return;
			}

			if(adj[i][j] == 9999) {
				return;
			}
			
			int x = q[i][j];	//intermediate node

			if(x == -1) {
				cout<<nodes[j]<<" ";
			}
			else {
				writePath(i, x);
				writePath(x, j);
			}
		}

		//calculating the distance between the nodes based on difference in ASCII values
		int stringMatch(string str1, string str2) {
			int count = 0;
			int distance = 0;

			if(str1.length() == str2.length()) {
				for(int i=0; i<str1.length(); i++) {
					if(str1[i] != str2[i]) {
						count++;
						if(count > 1) {
							return 99999;
						}
						distance = int(str1[i]) > int(str2[i]) ? int(str1[i]) - int(str2[i]) : int(str2[i]) - int(str1[i]);
					}
				}
				return distance;
			}
			return 99999;
		}

		//defining adjacency matrix
		void makeAdjacencyMatrix() {
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					adj[i][j] = stringMatch(nodes[i], nodes[j]);
					q[i][j] = -1;
					adjCopy[i][j] = adj[i][j];
				}
			}
		}

		//flyod warshall algorithm
		void algorithm() {
			for(int k=0; k<n; k++) {
		    	for(int i=0; i<n; i++) {
					for(int j=0; j<n; j++) {
						if(adj[i][j] > (adj[i][k] + adj[k][j])) {
							adj[i][j] = adj[i][k] + adj[k][j];

							//Noting down the k value in another matrix
							//Extra Credit 
							q[i][j] = k;
						}
					}
				}
			}
		}
};

int main() {
	int n, m;
	cin>>n;

	Flyod f = Flyod(n);
	f.inputNodes();
	f.makeAdjacencyMatrix();
	f.algorithm();

	cin>>m;
	f.inputPairs(m);

	f.outputAverage();
	f.outputPaths();

	return 0;
}