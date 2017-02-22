/**
 *	Maximum Flow
 * 	@author Rachit Shrivastava
 *  @email rshriva@ncsu.edu
 *
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class NetworkFlow {
	int n;
	int path_flow, max_flow;
	vector<bool> nodeState;			
	vector< vector<int> > adj;
	vector< vector<int> > res;	//residual graph matrix - copy of adj matrix
	vector<int> queue;
	vector<int> parent;
	vector< vector<int> > order;

public:

	NetworkFlow(int no) {
		n = no;
		path_flow = INT_MAX;
		max_flow = 0;
		nodeState.resize(n, false);
		adj.resize(n, vector<int> (n));
		res.resize(n, vector<int> (n));
		parent.resize(n);
	}

	//create adjacency matrix for directed graph by reading inputs
	void input(int m) {
		int i, j, data;
		order.resize(m, vector<int> (2));

		for(int k=0; k<m; k++) {
			cin>>i>>j>>data;
			adj[i][j] = data;
			res[i][j] = adj[i][j];
			order[k][0] = i;
			order[k][1] = j;
		}
	}

	bool bfs(int source, int sink) {
		int u;
		
		for(int i=0; i<n; i++) {
			nodeState[i] = false;
		}

		//set source as 0 node
		nodeState[source] = true;
		queue.push_back(source);
		parent[source] = -1;

		while(queue.size() > 0) {
			//remove first element
			u = queue[0];
			queue.erase(queue.begin());
			
			for(int i=0; i<n; i++) {
				if(!nodeState[i] && res[u][i] > 0) {
					queue.push_back(i);
					parent[i] = u;
					nodeState[i] = true;
				}
			}
		}

		return nodeState[sink];
	}

	void output() {
		int x, y;
		for(int i=0; i<order.size(); i++) {
			x = order[i][0];
			y = order[i][1];
			cout<<x<<" "<<y<<" "<<res[y][x]<<"\n";
		}
	}

	void algorithm() {
		//setting up source as 0 and sink as 1
		int source = 0;
		int sink = 1;
		
		while(bfs(source, sink)) {

	        int u, i = sink;
	        //min residual capacity on reverse graph
	        while(i != source) {
	        	int p = parent[i];
	        	path_flow = min(path_flow, res[p][i]);
	        	i = parent[i];
	        }
	 
	        // update residual values of the edges and reverse edges along the path
	        i = sink;
	        while(i != source) {
	        	u = parent[i];
	            res[u][i] -= path_flow;
	            res[i][u] += path_flow;
	            i = parent[i];
	        }

	        max_flow += path_flow;
	    }

	    cout<<max_flow<<endl;
	}

};

int main() {
	int n, m;
	cin>>n;
	NetworkFlow nf = NetworkFlow(n);

	cin>>m;
	nf.input(m);	
	nf.algorithm();
	nf.output();

	return 0;
}