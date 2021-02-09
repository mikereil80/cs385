/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Michael Reilly
 * Version     : 1.0
 * Date        : 10/25/19
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long inversions=0;
	for(int i=0; i<length-1; i++){
		for(int j=i+1; j<length; j++){
			if(array[i]>array[j]){
				inversions++;
			}
		}
	}
	return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	long inversions=0;
	int* scratch=new int[length];
	inversions+=mergesort(array, scratch, 0, length-1);
	delete[] scratch;
	return inversions;
}

static long merge(int array[], int scratch[], int low, int mid1, int mid2, int high){
	// helper function for mergesort
	long inversions=0;
	int l=low;
	int m=mid2;
	int l2=low;
	while((l<=mid1)&&(m<=high)){
		if(array[l]<=array[m]){
			scratch[l2++]=array[l++];
		}
		else{
			scratch[l2++]=array[m++];
			inversions+=(mid2-l);
		}
	}
	while(l<=mid1){
		scratch[l2++]=array[l++];
	}
	while(m<=high){
		scratch[l2++]=array[m++];
	}
	for(int i=low; i<=high; i++){
		array[i]=scratch[i];
	}
	return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long inversions=0;
	if(low<high){
		int mid=low+(high-low)/2;
		inversions+=mergesort(array, scratch, low, mid);
		inversions+=mergesort(array, scratch, mid+1, high);
		inversions+=merge(array, scratch, low, mid, mid+1, high);
	}
	return inversions;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	
	if(argc>2){
		cerr << "Usage: ./inversioncounter [slow]" << endl;
		return 1;
	}
	else{
		stringstream ss;
		if(argv[1]!=NULL){
			ss << argv[1];
			if(ss.str()!="slow"){
				cerr << "Error: Unrecognized option '" << ss.str() << "'." << endl;
				return 1;
			}
		}
		ss.clear();
		cout << "Enter sequence of integers, each followed by a space: " << flush;
	
		istringstream iss;
		int value, index = 0;
		vector<int> values;
		string str;
		str.reserve(11);
		char c;
		while (true) {
			c = getchar();
			const bool eoln = c == '\r' || c == '\n';
			if (isspace(c) || eoln) {
				if (str.length() > 0) {
					iss.str(str);
					if (iss >> value) {
						values.push_back(value);
					} else {
						cerr << "Error: Non-integer value '" << str
							<< "' received at index " << index << "." << endl;
						return 1;
					}
					iss.clear();
					++index;
				}
				if (eoln) {
					break;
				}
				str.clear();
			} else {
				str += c;
			}
		}
	
	
	// TODO: produce output
	
	int size=values.size();
	if(size==0){
		cerr << "Error: Sequence of integers not received." << endl;
		return 1;
	}
	if(argv[1]!=NULL){
		ss << argv[1];
		cout << "Number of inversions: " << count_inversions_slow(&values[0], size) << endl;
		return 0;
	}
	else{
		cout << "Number of inversions: " << count_inversions_fast(&values[0], size) << endl;
		return 0;
	}
	
    return 0;
	}
}