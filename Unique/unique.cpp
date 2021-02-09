/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Michael Reilly
 * Date        : September 20, 2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	
	// Loops through the string, and checks each position if they are a first in the English alphabet
	// and then if they are a lowercase letter
	// using c++ built in isalpha and islower to check if the letter is a lowercase letter in the English alphabet
	// if the character is not islower, returns false
	// otherwise returns true
	for(unsigned int pos=0; pos<s.length(); pos++){
		char current=s[pos];
		if(isalpha(current)==false){
			return false;
		}
		else{
			if(islower(current)==false){
				return false;
			}
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	
	// Loops through the string, finding the character value of each index compared to the lowest character of 'a'
	// Then checks if counter or the position are greater than 0, then the character can't be unique and must be false
	// otherwise return true
	int counter=0;
	for(unsigned int pos=0; pos<s.length(); pos++){
		unsigned int character=s.at(pos)-'a';
		if((counter & (1<< character))>0){
			return false;
		}
		else{
			counter = counter | (1 << character);
		}
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	
	if (argc!=2){ // Checks to make sure the input in command line fits the necessary argument conditions
		cout << "Usage: ./unique <string>" << endl;
		return 0;
	}
	if(is_all_lowercase(argv[1])==true){ // Checks if all letters are lowercase
		if(all_unique_letters(argv[1])==true){ // Then checks if all letters are unique
			cout << "All letters are unique." << endl;
			return 0;
		}
		else{
			cout << "Duplicate letters found." << endl;
			return 0;
		}
	}
	cerr << "Error: String must contain only lowercase letters." << endl; // If it is now all lowercase letters it is an error
	return 0;
}
