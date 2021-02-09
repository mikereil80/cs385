/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Michael Reilly
 * Date        : 9/29/19
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;
	vector<vector<int>> result;
	vector<int> empty;
	if(num_stairs<=0){ // need to check to make sure that the number of stairs is a positive integer
		ways.push_back(empty); // will append an empty vector to the vector if it is less than or equal to 0
	}
	else{
		for(int i=1; i<4; i++){ // since we're assuming you can go up a max of three stairs, and assuming you always take a step up the stairs, it will only be checking for values 1 to 3
			if(num_stairs>=i){ // checks to see if the recursive call can be made or not.
				result=get_ways(num_stairs-i); // recursively calls the get_ways function to cover all possible ways of getting up the stairs
				for(unsigned int j=0; j<result.size(); j++){ // j is an unsigned int because result.size() returns an unsigned int
					result.at(j).push_back(i);
				}
				ways.insert(ways.end(), result.begin(), result.end()); // use insert in order to put a vector into another vector.
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	for (unsigned int i = 0; i < ways.size(); i++){ // same reasoning as before with .size()
		if (ways.size()>9){ // if size is greater than 9, the formatting of the test script changes so have to account for that.
			if (i<9){ // only the non-double-digits need the space before them, for formatting reasons
				cout << " " << i+1 << ". " << "[";
			}
			else{
				cout << i+1 << ". " << "[";
			}
		}
		else{
			cout << i+1 << ". " << "[";
		}
		for (unsigned int j = ways[i].size()-1; j>0; j--){ // same reasoning as before with .size()
			cout << ways[i][j] << ", ";
		}
		cout << ways[i][0];
		cout << "]" << endl;
	}
}

int main(int argc, char * const argv[]) {
	if((argc==1) || (argc>2)){ // weeds out bad inputs of too many or too little arguments into command line
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}
	istringstream iss(argv[1]);
	int num;
	if(!(iss >> num)){ // needs to check if the input in command line is an integer
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	iss.clear();
	if(num<=0){ // then needs to check if the input in command line is an integer greater than 0, or else it can't be climbed
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	int number=get_ways(num).size();
	if(number==1){ // if one, use proper grammar, so must change all plural words to singular words.
		cout << number << " way to climb " << num << " stair." << endl;
	}
	else{
		cout << number << " ways to climb " << num << " stairs." << endl;
	}
	display_ways(get_ways(num));
	return 0;
}
