/**
 *	Line-Sweep Algorithm for Line Segment Intersection
 *
 * 	@author Rachit Shrivastava
 *  @email rshriva@ncsu.edu
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

/**
 * Point class
 * stores the given points using this class
 * Every point has x y co-ordinate, line no and a flag to depict if its the start point
 * it has functions to calculate dotProducts, crossProducts, and minus (-) operator overloaded
 */
class Point {
	float x, y;
	long long int lineNo;
	bool isStart;

public:
	void setPoint(float p1, float p2) {
		x = p1;
		y = p2;
	}

	void setDetails(long long int no, string str) {
		lineNo = no;
		isStart = (str.compare("start") == 0) ? true : false;
	}

	float getX() {
		return x;
	}

	float getY() {
		return y;
	}

	long long int getLineNumber() {
		return lineNo;
	}

	bool getIsStart() {
		return isStart;
	}

	// Overload - operator to subtract two Point objects.
	Point operator - (const Point& p) {
		Point point;
		point.setPoint(this->x - p.x, this->y - p.y);
		return point;
	}

	float crossProduct(Point p) {
		return x*p.getY() - y*p.getX();
	}

	float dotProduct(Point p) {
		return x*p.getX() + y*p.getY();
	}

	void display() {
		cout<<x<<" "<<y<<" ... "<<lineNo<<endl;
	}
};

/**
 * Line class
 * sets up a line segment with start and end points
 * has functions to check for point direction, if its on segment, if line segment intersect, if yes then where?
 */
class Line {
	Point start, end;

public:
	void setLine(Point p1, Point p2) {
		if(p1.getIsStart()) {
			start.setPoint(p1.getX(), p1.getY());
			start.setDetails(p1.getLineNumber(), p1.getIsStart() ? "start" : "end");

			end.setPoint(p2.getX(), p2.getY());
			end.setDetails(p2.getLineNumber(), p2.getIsStart() ? "start" : "end");
		}
		else {
			start.setPoint(p2.getX(), p2.getY());
			start.setDetails(p2.getLineNumber(), p2.getIsStart() ? "start" : "end");

			end.setPoint(p1.getX(), p1.getY());	
			end.setDetails(p1.getLineNumber(), p1.getIsStart() ? "start" : "end");
		}
	}

	Point getStart() {
		return start;
	}

	Point getEnd() {
		return end;
	}

	//display the start and end points of the line - debugging
	void display() {
		cout<<"Start: ";
		start.display();
		cout<<"End: ";
		end.display();
	}

	//check if the point p lies on which side of the line segment qr
	float directionCheck(Point p, Point q, Point r) {
		Point t1 = p-q;
		Point t2 = r-q;
		return t1.crossProduct(t2);
	}

	//to check if point p lies on the line segment qr
	bool onSegment(Point p, Point q, Point r) {
	    if(p.getX() >= min(q.getX(), r.getX()) && p.getX() <= max(q.getX(), r.getX()) &&
	    	p.getY() >= min(q.getY(), r.getY()) && p.getY() <= max(q.getY(), r.getY()))
	       return true;

	    return false;
	}

	//find if the given set of lines intersects or not
	bool intersects(Line l) {
		float a1 = directionCheck(l.getEnd(), start, end);	
		float a2 = directionCheck(l.getStart(), start, end); 

		float b1 = directionCheck(end, l.getStart(), l.getEnd()); 
		float b2 = directionCheck(start, l.getStart(), l.getEnd()); 

		if(a1*a2 < 0 && b1*b2 < 0)
			return true;
		if(a1 == 0 && onSegment(l.getEnd(), start, end))
			return true;
		if(a2 == 0 && onSegment(l.getStart(), start, end))
			return true;
		if(b1 == 0 && onSegment(end, l.getStart(), l.getEnd()))
			return true;
		if(b2 == 0 && onSegment(start, l.getStart(), l.getEnd()))
			return true;

		return false;
	}

	//calculating the intersection for given two lines
	void findIntersection(Line l) {
		Point p1 = start;
		Point p2 = end;
		Point p3 = l.getStart();
		Point p4 = l.getEnd();
		//cout<<"p1 "<<p1.display();

		float denominator = (p2-p1).crossProduct(p4-p3);
		//if(denominator != 0)
		float t = (p4-p3).crossProduct(p1-p3) / denominator;
		//cout<<t<<endl;

		//point of intersection
		float x = start.getX() + t * (end.getX() - start.getX());
		float y = start.getY() + t * (end.getY() - start.getY());

		cout<<setprecision(2)<<fixed<<x<<" "<<y<<endl;
	}
};


//for insert functionality
int findPosition(vector<int> order, vector<Line> lines, Point p) {
	int i;
	if(order.size() > 0) {
		for(i=0; i<order.size(); i++) {
			if(p.getY() <= lines[order[i]].getStart().getY()) {
				return i;
			}
		}
		return i;
	}
	else {
		return 0;
	}
}

//for erase functionality
int findPosition(vector<int> order, int lineNo) {
	for(int i=0; i<order.size(); i++) {
		if(lineNo == order[i]) {
			//cout<<i<<" >> "<<order[i]<<endl;
			return i;
		}
	}
	return -1;
}

//comparator class for priority queue to store points given in the form a heap
class comparator {
public:
    bool operator() (Point& l, Point& r) {
        if(l.getX() > r.getX()) {
			return true;
		}
		else if(l.getX() == r.getX()) {
			if(l.getY() > r.getY()) {
				return true;
			}
		}
		
		return false;
    }
};

//Self balancing binary search tree implmented using multimap
class BST {
	multimap<float, Point> order;
	bool hasPrev, hasNext;
	Point prev, next;
	vector<Line> lines;

public:
	void setLines(vector<Line> l) {
		for(long long int i=0; i<l.size(); i++) {
			lines.push_back(l[i]);
		}
	}

	void hasNeighbors(Point p) {
		multimap<float, Point> ::iterator it;
		Point point;

		for(it = order.begin(); it != order.end(); it++) {
			point = it->second;
	    	if(point.getY() < p.getY()) {
	    		prev = point;
				hasPrev = true;
	    	} 
	    	else if(point.getY() > p.getY()) {
	    		next = point;
				hasNext = true;
	    		break;
	    	}
		}
	}

	void display() {
		multimap<float, Point> ::iterator it;
		Point p;
		for(it = order.begin(); it != order.end(); it++) {
			p = it->second;
			cout<<p.getLineNumber()<<" ";
		}
	}

	void sweepAlgorithm(Point currPoint) {
		int one, two;
		hasPrev = false;
		hasNext = false;
	
		hasNeighbors(currPoint); //values for prev, next and flags have been set now

		if(currPoint.getIsStart()) {
			//insert the Point into order - it will have line number as well
			order.insert(pair<float, Point>(currPoint.getY(), currPoint));
			//display();cout<<endl;
			//check for previous line/point - up neighbor
			if(hasPrev) {
				one = currPoint.getLineNumber();
				two = prev.getLineNumber();
				if(lines[one].intersects(lines[two]) && one != two) {
					//lines[one].findIntersection(lines[two]);
					cout<<one<<" "<<two<<endl;
				}
			}

			//check for next line - down neighbor
			if(hasNext) {
				one = currPoint.getLineNumber();
				two = next.getLineNumber();
				if(lines[one].intersects(lines[two]) && one != two) {
					//lines[one].findIntersection(lines[two]);
					cout<<one<<" "<<two<<endl;
				}
			}
		}
		else {
			if(hasPrev && hasNext) {
				one = prev.getLineNumber();
				two = next.getLineNumber();
				if(lines[one].intersects(lines[two]) && one != two) {
					//lines[one].findIntersection(lines[two]);
					cout<<one<<" "<<two<<endl;
				}

				two = next.getLineNumber();
				if(lines[one].intersects(lines[two]) && one != two) {
					//lines[one].findIntersection(lines[two]);
					cout<<one<<" "<<two<<endl;
				}
			}
			// Delete from order tree
			order.erase(lines[currPoint.getLineNumber()].getStart().getY());
			//order.erase(currPoint.getY());
			//display();cout<<endl;
		}
	}
};

//Main function
int main() {
	long long int i, n;
	float x1, x2, y1, y2;
	BST bst;
	Line l;
	Point p1, p2;
	vector<Line> lines;
	std::priority_queue<Point, vector<Point>, comparator> pq;

	//number of line segments
	cin>>n;

	//read in and store the input
	for(i = 0; i < n; i++) {
		cin>>x1>>y1>>x2>>y2;

		p1.setPoint(x1, y1);
		p2.setPoint(x2, y2);
		
		if(x1 < x2) {
			p1.setDetails(i, "start");
			p2.setDetails(i, "end");
			l.setLine(p1, p2);
		}
		else {
			p1.setDetails(i, "end");
			p2.setDetails(i, "start");
			l.setLine(p2, p1);
		}

		pq.push(p1);	pq.push(p2);
		lines.push_back(l);
	}

	bst.setLines(lines);

	//inserting and deleting the line numbers as per the sweep
    while(!pq.empty()) {

		Point point = pq.top();
		bst.sweepAlgorithm(point);
		pq.pop();
	}

	return 0;
}

		/*lineNo = point.getLineNumber();

		if(point.getIsStart()) {
			pos = findPosition(order, lines, point);
			
			order.insert(order.begin()+pos, lineNo);
			//for(int j=0; j<order.size(); j++) {
			//	cout<<order[j]<<" ";
			//}cout<<endl;

			//check the new neighbors for intersection
			if(order.size() > 1 && pos < order.size() && pos >= 0) {
				if(pos != order.size()-1) {
					if(lines[order[pos]].intersects(lines[order[pos+1]])) {
						lines[order[pos]].findIntersection(lines[order[pos+1]]);
						break;
					}
				}
				if(pos != 0) {
					if(lines[order[pos]].intersects(lines[order[pos-1]])) {
						lines[order[pos]].findIntersection(lines[order[pos-1]]);
						break;
					}
				}
			}
		} 
		else {
			//find the position of lineNo in order
			//erase it
			pos = findPosition(order, lineNo);

			if(pos >= 0) {
				order.erase(order.begin()+pos);
				//for(int j=0; j<order.size(); j++) {
				//	cout<<order[j]<<" ";
				//}cout<<endl;
			}

			//check the new neighbors for intersection
			if(order.size() > 1 && pos < order.size() && pos >= 0) {
				if(pos != order.size()-1) {
					if(lines[order[pos]].intersects(lines[order[pos+1]])) {
						lines[order[pos]].findIntersection(lines[order[pos+1]]);
						break;
					}
				}
				if(pos != 0) {
					if(lines[order[pos]].intersects(lines[order[pos-1]])) {
						lines[order[pos]].findIntersection(lines[order[pos-1]]);
						break;
					}
				}
			}
		}*/