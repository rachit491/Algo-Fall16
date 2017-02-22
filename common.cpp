/**
 * To find distinct substrings in give two strings
 * @author Rachit Shrivastava
 *
 * The code firstly extracts substings from the smallest string inputted (search string)
 * for each substring it then searches the parent string (second inputted string)
 * Compare newly found sub-string in the list
 * if a new distinct sub-string is found store it in list, count++
 * display count
 */


#include <iostream>
#include <string>
#include <vector>
using namespace std;

size_t searchSubstr(string search, string parent) {
	size_t index;
	//to find the desired substring 
	index = parent.find(search);	

	if(index != std::string::npos && index <= parent.length())	//static number constant for size_t greatest possible value
		return index;
	else
		return parent.length()+1;
}

int main() {
	//input strings
	string str1, str2, search, parent;
	vector<string> list;
	int count = 0;
	bool addNew = true;
	size_t found = -1, end = 0;
	
	cout<<"Input two strings: \n";
	cin>>str1;
	cin>>str2;
	
	//Considering only lowercase
	//therefore, converting uppercase characters into lowercase
	for(int i=0;i<str1.length();i++){
		str1[i]=tolower(str1[i]);
	}
	for(int i=0;i<str2.length();i++){
		str2[i]=tolower(str2[i]);
	}

	//Making smaller string to be searched in bigger one
	search = str1;
	parent = str2;
	if(str2.length() < str1.length()) {
		search = str2;
		parent = str1;
	}

	for(int endPointer = search.length()-1; endPointer >= 0; endPointer--) {
		for(int startPointer = 0; startPointer <= endPointer; startPointer++) {
			end = endPointer+1-startPointer;
			//clearing off temp variable
			//Creates a substring from specified positions
			string temp = search.substr(startPointer, end);
			
			//cout<<temp<<"\n";															// For debugging
			found = searchSubstr(temp, parent);
			//cout<<"Here - "<<found <<"\n";											// For debugging
			if(found <= parent.length()) {	//if found
				if(count > 0) {
					addNew = true;
					//Making a note of items found
					for(int k = 0; k < list.size(); k++) {
						//compares every element from the list to newly found sub-string in parent string
						if(list[k].compare(temp) == 0) {
							addNew = false;
							break;
						}
					}
				}
				if(addNew) { 
					list.push_back(temp);	//Adds newly found substring in a list
					//cout<<count<<" - Found - "<<found<<" "<<temp<<"\n";				// For debugging
					count++;	//Counter
				}
			}
		}		
	}

	//Display Result
	cout<<count;

	return 0;
}