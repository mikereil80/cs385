/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Michael Reilly
 * Version     : 1.0
 * Date        : 12/3/19
 * Description : Finds the shortest path from one vertex to another using Floyd's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

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
long num_vertices=0;
const long INF=numeric_limits<long>::max();
long** matrix;
long** d;
long** paths;
long** intermediate;

int len(int num){
	int digits=1;
	while(num>=10){
		digits++;
		num/=10;
	}
	return digits;
}

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
    int max_cell_width = use_letters ? len(max_val) :             
		len(max(static_cast<long>(num_vertices), max_val));     
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
			} 
			else if (use_letters) {                 
				cout << static_cast<char>(matrix[i][j] + 'A');             
			} 
			else {                 
				cout << matrix[i][j];             
			}         
		}         
		cout << endl;    
	}     
	cout << endl; 
}

void floyds_algorithm(long** adjacency){
	d=new long*[num_vertices];
	for(int x=0; x<num_vertices; x++){
		d[x]=new long[num_vertices];
		fill_n(d[x], num_vertices, INF);
	}
	paths=new long*[num_vertices];
	for(int x=0; x<num_vertices; x++){
		paths[x]=new long[num_vertices];
		for(int y=0; y<num_vertices; y++){
			paths[x][y]=adjacency[x][y];
		}
	}
	intermediate=new long*[num_vertices];
	for(int x=0; x<num_vertices; x++){
		intermediate[x]=new long[num_vertices];
		fill_n(intermediate[x], num_vertices, INF);
	}
	for(int k=0; k<num_vertices; k++){
		for(int i=0; i<num_vertices; i++){
			for(int j=0; j<num_vertices; j++){
				if(paths[i][k]!=INF && paths[k][j]!=INF && paths[i][j]>(paths[i][k]+paths[k][j])){
					paths[i][j]=paths[i][k]+paths[k][j];
					intermediate[i][j]=k;
				}
				if(i==j){
					adjacency[i][j]=0;
					paths[i][j]=0;
					intermediate[i][j]=INF;
				}
			}
		}
	}
	display_table(adjacency, "Distance matrix:", false);
	display_table(paths, "Path lengths:", false);
	display_table(intermediate, "Intermediate vertices:", true);
}

void add_matrix(char c1, char c2, int weight){
	matrix[c1-'A'][c2-'A']=weight;
}

vector<char> backtrack(int x, int y){
	vector<char> ans;
	char c1;
	char c2;
	if(intermediate[x][y]==INF){
		c1='A'+x;
		c2='A'+y;
		ans.push_back(c2);
		if(c1!=c2){
			ans.push_back(c1);
		}
		return ans;
	}
	else{
		ans=backtrack(x, intermediate[x][y]);
		vector<char> v2=backtrack(intermediate[x][y], y);
		v2.insert(v2.end(), ans.begin()+1, ans.end());
		return v2;
	}
}

void display_path(){
	vector<char> p;
	for(int i=0; i<num_vertices; i++){
		for(int j=0; j<num_vertices; j++){
			p=backtrack(i, j);
			reverse(p.begin(), p.end());
			int c1='A'+i;
			int c2='A'+j;
			cout << static_cast<char>(c1) << " -> " << static_cast<char>(c2) << ", distance: ";
			if(paths[i][j]<INF){
				cout << paths[i][j] << ", path: " << p.at(0);
				for(unsigned int k=1; k<p.size(); k++){
					cout << " -> " << p.at(k);
				}
			}
			else{
				cout << "infinity, path: none";
			}
			cout << endl;
		}
	}
}

bool read_line(string s, int num_line){
	istringstream iss(s);
	vector<string> line;
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(line));
	if(line.size() != 3){
		cerr << "Error: Invalid edge data '" << s << "' on line " << num_line << "." << endl;
		return false;
	}
	char max = 'A' + num_vertices - 1;
	int weight = 0;
	char c1, c2;
	for(int i = 0; i < 3; ++i){
		if(line[i].size() != 1){
			if(i == 0){
				cerr << "Error: Starting vertex '" << line[i] << "' on line " << num_line << " is not among valid values A-"<< max <<"."<<endl;
				return false;
			}else if(i==1){
				cerr << "Error: Ending vertex '" << line[i] << "' on line " << num_line << " is not among valid values A-"<< max <<"."<<endl;
				return false;
			}
		}
		if(line[i].at(0) < 'A' || line[i].at(0) > max){
			if(i == 0){
				cerr << "Error: Starting vertex '" << line[i] << "' on line " << num_line << " is not among valid values A-"<< max <<"."<<endl;
				return false;
			}else if(i==1){
				cerr << "Error: Ending vertex '" << line[i] << "' on line " << num_line << " is not among valid values A-"<< max <<"."<<endl;
				return false;
			}
		}
		istringstream iss;
		if(i==0){
			c1 = line[0].at(0);
		}
		else if(i==1){
			c2 = line[1].at(0);
		}
		else if(i==2){
			iss.str(line[i]);
			if(!(iss >> weight)){
				cerr << "Error: Invalid edge weight '" << line[2] << "' on line " << num_line << "." << endl;
				return false;
			}
			if(weight < 1){
				cerr << "Error: Invalid edge weight '" << line[2] << "' on line " << num_line << "." << endl;
				return false;
			}
		}
	}
	add_matrix(c1,c2,weight);
	return true;
}

void delete_matrix(){
	for(int i=0; i<num_vertices; i++){
		delete matrix[i];
		delete d[i];
		delete paths[i];
		delete intermediate[i];
	}
}
 
int main(int argc, char *argv[]){
	if(argc!=2){
		cerr << "Usage: ./shortestpaths <filename>" << endl;
		return 1;
	}
	ifstream input_file(argv[1]);
	if(!input_file){
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	string line;
	unsigned int num_line=1;
	while(getline(input_file, line)){
		if(num_line==1){
			istringstream iss;
			iss.str(line);
			if(!(iss>>num_vertices)){
				cerr << "Error: Invalid number of vertices '" << line << "' on line " << num_line << "." << endl;
				return 1;
			}
			if(num_vertices<1||num_vertices>26){
				cerr << "Error: Invalid number of vertices '" << line << "' on line " << num_line << "." << endl;
				return 1;
			}
			matrix = new long*[num_vertices];
			for(int i=0; i<num_vertices; i++){
				matrix[i]=new long[num_vertices];
				fill_n(matrix[i], num_vertices, INF);
			}
		}
		else{
			if(!read_line(line, num_line)){
				return 1;
			}
		}
		num_line++;
	}
	floyds_algorithm(matrix);
	display_path();
	input_file.close();
	delete_matrix();
	return 0;
}