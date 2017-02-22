/**
 *	KMP and Performance Evaluation
 *
 * 	@author Rachit Shrivastava
 *  @email rshriva@ncsu.edu
 *
 *	The following code determines the timings for three different types of 
 *  String Matching Algorithms - Naive, C++ inbuilt, KMP
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <sys/time.h>

using namespace std;

//The class which has function for Naive and KMP alogirthms
class PatternMatcher {

	string pattern, txt;
	vector<int> prefixArray;	// vector to store prefix array

public:
	PatternMatcher(string ptn, string str) {
		pattern = ptn;
		txt = str;
		//default values for prefixArray is 0
		prefixArray.resize(pattern.length(), 0);
	}

	vector<int> getPrefixArray() {
		return prefixArray;
	}

	//Fills prefix array[] for given pattern
	void computePrefixArray() {
	    int len = 0;
	    prefixArray[0] = 0; // first index is always 0
	 
	    int i = 1;
	    while(i < pattern.length()) {
	        if(pattern[i] == pattern[len]) {
	            len++;
	            prefixArray[i] = len;
	            i++;
	        }
	        else { //when (pattern[len] != pattern[i])
	            if(len != 0) {
	                len = prefixArray[len-1];
	            }
	            else {
	                prefixArray[i] = 0;
	                i++;
	            }
	        }
	    }
	}

	//KMP string search algorithm
	void KMPSearch() {
	    long long int i = 0, j = 0;
	    long long int n = txt.length();
	    long long int m = pattern.length();
	    bool found = false;

	    computePrefixArray();

	    for(i = 0; i < n; i++) {
	    	while(j > 0 && pattern[j] != txt[i]) {
	    		j = prefixArray[j-1];
	    	}

	    	if(pattern[j] == txt[i]) {
	    		j++;
	    	}
	    	if(j == m) {
	    		cout<<"found at: " << i-j+1 <<endl;
	            //j = prefixArray[j-1];
	            found = true;
	            break;
	    	}
	    }

	    if(!found) {
	    	cout<<"found at: -1"<<endl;
	    }
	}

	//naive algorithm for string matching
	//it matches pattern from begining eveytime
	void Naive() {
		long long int i, j;
		long long int n = txt.length();
		long long int m = pattern.length();
		bool found = false;

		for(i=0; i<=(n-m); i++) {
			for(j=0; j<m; j++) {
				if(txt[i+j] != pattern[j]) {
					break;
				}
			}

			if(j == m && !found) {
				cout<<"found at: " << i <<endl;
				found = true;
			}
		}

		if(!found) {
			cout<<"found at: -1"<<endl;
		}
	}
};

//Get current time
long long int getMilliseconds() {
    timeval tv;
    gettimeofday( &tv, NULL );
    long int ms = tv.tv_sec;
    ms = ms * 1000 + tv.tv_usec / 1000;
    return ms;
}

//generates random string with or without pattern in it
string generateString(string values, string pattern) {
	long long int i, MAX = (rand() % 10000) + 90000;
	int x, y;
	string str = "";
	int len = pattern.length();

	//inserting dummy vaues for first 9000000+ characters
	for(i=0; i<MAX; i++) {
		str += pattern.substr(0, len-2);
		y = rand() % values.length();			//getting random values from alphabets not used in pattern
		str += values[y];
	}

	if(MAX % 7 != 0) {
		//include the pattern only if the MAX value is not a multiple of 7
		str += pattern;
		y = rand() % values.length();			
		str += values[y];
		
		for(i=0; i<10000; i++) {
			x = rand() % (len-2);
			str += pattern.substr(0, x);
			y = rand() % values.length();			//getting random values from alphabets not used in pattern
			str += values[y];
		}
	}

	return str;
}

//geerates random pattern
string generatePattern(string values) {
	int i, x;
	string pattern = "";
	int size = (rand() % 20) + 50;

	x = rand() % values.length();
	for(i=0; i<size; i++) {
		pattern += values[x];
	}

	return pattern;
}

//read file input
vector<string> readFileToVector(string filename) {
    ifstream source;
    source.open(filename.c_str());
    vector<string> lines;
    string line;
    while (getline(source, line)) {
        lines.push_back(line);
    }
    return lines;
}

//Main function
int main(int argc, char* argv[]) {
    string txt;
    string pattern;
    long long int t0, t1;
    string ptnValues = "abcde";
    string values = "fghijklmnopqrstuvwxyz";	//all alphabets except those used in pattern

    if(argc == 2) {
    	//read from file if argument length is 2
    	string matchesFilename(argv[1]);
    	vector<string> matches = readFileToVector(matchesFilename);
    	txt = matches[0];
    	pattern = matches[1];
    }
    else {
    	//generates random pattern and haystack to test upon
	    srand(time(NULL));
	    pattern = generatePattern(ptnValues);
	    txt = generateString(values, pattern);
	    //cout<<txt<<endl<<pattern;
    }

    //initializes the PatternMatcher class
    PatternMatcher example = PatternMatcher(pattern, txt);
    
    t0 = getMilliseconds();  
    example.Naive();	//call the naive algo
    t1 = getMilliseconds();  
    cout<<"naive search time: "<<t1-t0<<endl;

    t0 = getMilliseconds();  
    long int loc = txt.find(pattern);		//default string matching algo in c++
    loc = (txt.length() > loc) ? loc : -1;
    cout<<"found at: "<<loc<<endl;
    t1 = getMilliseconds();  
    cout<<"standard search time: "<<t1-t0<<endl;

    //calls to compute the prefix array
    t0 = getMilliseconds();  
    example.KMPSearch();			//KMP algorithm
    t1 = getMilliseconds();  
    cout<<"kmp search time: "<<t1-t0<<endl;
	
    return 0;
}