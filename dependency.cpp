/**
 *	Strongly Connected Components
 * 	@author Rachit Shrivastava
 *  @email rshriva@ncsu.edu
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Class to represent a single Node of graph
class Node {
	string name;
	string color;

public:
	string getName() {
		return name;
	}

	string getColor() {
		return color;
	}

	void setName(string val) {
		name = val;
	}

	void setColor(string val) {
		color = val;
	}
};

//Functions related to the graph
class Graph {
	int i, j;

	vector<Node> vertex;
	vector<int> order;
	vector<string> edges;
	vector<vector <int> > adj, rev;
	vector<vector <int> > result;
	vector<int> arr;
	std::vector<int>::iterator it;

	Node dummy;
	string str;

public:
	Graph(int n) {

		for(i = 0; i < n; i++) {
			getline(cin, str);
			dummy.setName(str);
			dummy.setColor("white");
			vertex.push_back(dummy);
		}
		
		//intialize adjacency matrix
		adj.resize(n, vector<int> (n, 0));
		rev.resize(n, vector<int> (n, 0));

	}

	void readEdges(int m) {
		
		for(i = 0; i < m; i++) {
			getline(cin, str);
			edges.push_back(str);

			makeAdjacencyMatrix(str);
		}

	}

	//get positions for vertex to make the adjacency matrix
	vector<int> getPositions(string s) {
		vector<int> pos(2);
		int x;
		string str;
		
		for(int k = 0; k < vertex.size(); k++) {

			x = s.find(vertex[k].getName());

			if(x == 0) {
				str = s.substr(x+vertex[k].getName().size(), 1);
				if(str.compare(" ") == 0) {
					pos[1] = k;
				}
			}

			if(x > 0 && x < s.size()) {
				//str = s.substr(x-1, 1);
				if(s.size() == x+vertex[k].getName().size()) {
					pos[0] = k;
				}
			}

		}

	    return pos;
	}

	void makeAdjacencyMatrix(string edge) {
		vector<int> loc(2);

		loc = getPositions(edge);
		//edge from i to j
		adj[loc[1]][loc[0]] = 1;
		rev[loc[0]][loc[1]] = 1;
	}

	//DFS recursive function
	void dfs(int index) {
		vertex[index].setColor("gray");

		for(int k=0; k<adj[index].size(); k++) {
			if(adj[index][k] == 1 && vertex[k].getColor().compare("white") == 0) {
				dfs(k);
			}
		}

		it = order.begin();
		it = order.insert(it, index);	//store the reverse order
	}

	//extract eac component
	void getComponents(int index) {
		arr.push_back(index);
		vertex[index].setColor("gray");

		for(int k=0; k<rev[index].size(); k++) {
			if(rev[index][k] == 1 && vertex[k].getColor().compare("white") == 0) {
				getComponents(k);
			}
		}
		vertex[index].setColor("black");
	}

	//custom sorting function
	bool static myFunction(vector<int> v1, vector<int> v2) {
		return (v1[0] < v2[0]);
	}

	void getSCC() {
		for(i = 0; i < vertex.size(); i++) {
			if(vertex[i].getColor().compare("white") == 0) {
				dfs(i);
			}
		}

		//reset color
		for(i = 0; i < vertex.size(); i++) {
			vertex[i].setColor("white");
		}

		//for i in order call dfs
		for(i = 0; i < order.size(); i++) {
			if(vertex[order[i]].getColor().compare("white") == 0) {
				getComponents(order[i]);
				sort(arr.begin(), arr.end());
				if(arr.size() > 1) {
					result.push_back(arr);
				}
				arr.clear();
			}
		}

		//sort the result as required
		sort(result.begin(), result.end(), myFunction);

		for(i = 0; i < result.size(); i++) {
			for(j = 0; j < result[i].size(); j++) {
				if(j != result[i].size()-1)
					cout<<vertex[result[i][j]].getName()<<" ";
				else
					cout<<vertex[result[i][j]].getName();
			}
			cout<<endl;
		}

	}

	//debugger function to display values at each step
	void display() {
		for(i=0;i<vertex.size();i++){
			cout<<vertex[i].getName()<<endl;
		}

		cout<<endl;
		for(i=0;i<edges.size();i++){
			cout<<edges[i]<<endl;
		}		

		cout<<endl;
		for(i=0;i<adj.size(); i++) {
			for(j=0; j<adj[i].size(); j++) {
				cout<<adj[i][j]<<" ";
			}
			cout<<endl;
		}

		cout<<endl;
		for(i=0;i<rev.size(); i++) {
			for(j=0; j<rev[i].size(); j++) {
				cout<<rev[i][j]<<" ";
			}
			cout<<endl;
		}

		cout<<endl;
		for(i=0; i<order.size();i++) {
			cout<<order[i]<<" ";
		}
	}

};

int main() {
	int n, m;
	string str;

	getline(cin, str);
	//create graph with n vertices
	n = atoi(str.c_str());
	Graph g(n);

	getline(cin, str);
	m = atoi(str.c_str());
	g.readEdges(m);

	g.getSCC();

	//g.display();

}