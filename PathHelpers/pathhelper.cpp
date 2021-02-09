/*
 * shortestpath.cpp
 *
 *  Created on: Nov 28, 2018
 *      Author: Adam Undus, Brandon Soong
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <limits>

using namespace std;
long num_vertices = 0;
const long INF = numeric_limits<long>::max();
long** matrix;
long** d1;
long** d2;
long** d3;


int len(int num) {
     //  determine how many digits are in an integer
     int digits = 1;
    while(num >= 10){
       	digits ++;
    	num /= 10;
    }
    return digits;
}

/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

// Implement floyds algorithm to get all shortest paths
void floyds_alg(long** adj_mat) {
	//long** d = adj_mat;
 	d1 = new long*[num_vertices];
 	for(int x = 0; x < num_vertices; x++) {
 		d1[x] = new long[num_vertices];
 		fill_n(d1[x],num_vertices,INF);
 	}
 	d2 = new long*[num_vertices];
 	 for(int x = 0; x < num_vertices; x++) {
 		d2[x] = new long[num_vertices];
 		for(int y = 0; y<num_vertices; ++y){
 			d2[x][y] = adj_mat[x][y];
 		}
 	}
 	d3 = new long*[num_vertices];
 	for(int x = 0; x < num_vertices; x++) {
 	 	d3[x] = new long[num_vertices];
 	 	fill_n(d3[x],num_vertices,INF);
	}
 	for(int k = 0; k < num_vertices; k++) {
 	    for(int i = 0; i < num_vertices; i++) {
 	        for(int j = 0; j < num_vertices; j++) {
 	            if(d2[i][k] != INF && d2[k][j] != INF && d2[i][j] > (d2[i][k] + d2[k][j])) {
	 	            	d2[i][j] = d2[i][k] + d2[k][j];
	 	            	d3[i][j] = k;
 	            }
 	            if(i == j){
 	            	adj_mat[i][j] = 0;
 	            	d2[i][j] = 0;
 	            	d3[i][j] = INF;
 	            }
 	        }
 	    }
 	}
 	display_table(adj_mat, "Distance matrix:" , false);
 	display_table(d2, "Path lengths:", false);
 	display_table(d3, "Intermediate vertices:", true);
 }

void addToMatrix(char v1, char v2, int edgeWeight){
	//simple function that adds the elements to the matrix
	matrix[v1-'A'][v2-'A'] = edgeWeight;
}

vector<char> backtrack(int x, int y){
	//backtracking function that retraces through the algorithm to gain the path
	vector<char> ans;
	char c1, c2;
	if(d3[x][y] == INF) {
		c1 = 'A' + x;
		c2 = 'A' + y;
		ans.push_back(c2);
		if(c1 != c2){
			ans.push_back(c1);
		}
		return ans;
	}else{
		ans = backtrack(x,d3[x][y]);
		vector<char> v2 = backtrack(d3[x][y],y);
		v2.insert(v2.end(),ans.begin()+1,ans.end());
		return v2;
	}
}

void printPath(){
	//prints the path that the algorithm follows
	vector<char> path;
	for(int i = 0; i<num_vertices;++i){
		for(int j = 0;j<num_vertices;++j){
			path = backtrack(i,j);
			reverse(path.begin(),path.end());
			cout << static_cast<char>('A'+i) << " -> " << static_cast<char>('A'+j) << ", distance: ";
			if(d2[i][j] < INF){
				cout << d2[i][j] << ", path: ";
				cout << path.at(0);
				for(unsigned int x = 1; x < path.size();++x){
					cout << " -> " << path.at(x);
				}
			}
			else{
				cout << "infinity, path: none";
			}
			cout << endl;
		}
	}
}

bool processLine(string s, int line_number){
	istringstream iss(s);
	vector<string> params;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(params));
	if(params.size() != 3){
		cerr << "Error: Invalid edge data '" << s << "' on line " << line_number<< "." << endl;
		return false;
	}
	char maxLetter = 'A' + num_vertices - 1;
	int edgeWeight = 0;
	char V1, V2;
	for(int i = 0; i < 3; ++i){
		if(params[i].size() != 1){
			if(i == 0){
				cerr << "Error: Starting vertex '" << params[i] << "' on line " << line_number << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}else if(i==1){
				cerr << "Error: Ending vertex '" << params[i] << "' on line " << line_number << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}
		}
		if(params[i].at(0) < 'A' || params[i].at(0) > maxLetter){
			if(i == 0){
				cerr << "Error: Starting vertex '" << params[i] << "' on line " << line_number << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}else if(i==1){
				cerr << "Error: Ending vertex '" << params[i] << "' on line " << line_number << " is not among valid values A-"<< maxLetter <<"."<<endl;
				return false;
			}
		}
		istringstream iss;
		if(i==0){
			V1 = params[0].at(0);
		}
		else if(i==1){
			V2 = params[1].at(0);
		}
		else if(i==2){
			iss.str(params[i]);
			if(!(iss >> edgeWeight)){
				cerr << "Error: Invalid edge weight '" << params[2] << "' on line " << line_number << "." << endl;
				return false;
			}
			if(edgeWeight < 1){
				cerr << "Error: Invalid edge weight '" << params[2] << "' on line " << line_number << "." << endl;
				return false;
			}
		}
	}
	addToMatrix(V1,V2,edgeWeight);
	return true;
}

void deleteMatrix(){
	for(int i=0;i<num_vertices;++i){
		delete matrix[i];
		delete d1[i];
		delete d2[i];
		delete d3[i];
		
	}
}

int main(int argc, char *argv[]) {
	// Make sure the right number of command line arguments exist.
	if (argc != 2 ) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}

	// Create an ifstream object.
	ifstream input_file(argv[1]);
	// If it does not exist, print an error message.
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(ifstream::badbit);
	string line;
	try {
		unsigned int line_number = 1;
		// Use getline to read in a line.
		// See http://www.cplusplus.com/reference/string/string/getline/
		while (getline(input_file, line)) {
			//cout << line_number << ":\t" << line << endl;
			if(line_number == 1){
				//num_vertices = stoi(line);
				istringstream iss;
				iss.str(line);
				if(! (iss >> num_vertices)){
					cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number <<"." << endl;
					return 1;
				}
				if(num_vertices < 1 || num_vertices > 26){
					cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number <<"." << endl;
					return 1;
				}
				matrix = new long*[num_vertices];
				for(int i = 0; i < num_vertices; ++i){
					matrix[i] = new long[num_vertices];
					fill_n(matrix[i] , num_vertices , INF);
				}
			}else{
				if(!processLine(line, line_number)){
					return 1;
				}
			}
			++line_number;
		}
		// Don't forget to close the file.
		floyds_alg(matrix);
		printPath();
		input_file.close();
		deleteMatrix();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}

	return 0;
}