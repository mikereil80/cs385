/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Michael Reilly
 * Date        : October 12, 2019
 * Description : Program to use breadth-first search to find the most efficient way to sort a set of 3 waterjugs with certain amounts in each one in the end, given all water is initially in the biggest jug.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int cap_a, cap_b, cap_c;
bool goal=false;
string pours;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
	
	State(int _a, int _b, int _c, vector<string> _directions) : a(_a), b(_b), c(_c), directions(_directions) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
	
	int get_a(){
		return a;
	}
	int get_b(){
		return b;
	}
	int get_c(){
		return c;
	}
	vector<string> get_directions(){
		return directions;
	}
	void print_states() {
		for (unsigned int i = 0; i < directions.size(); ++i) {
			cout << directions[i] << endl;
		}
	}
};

vector<string> make_initial_state(int a, int b, int c){
	vector<string> initial;
	stringstream ss;
	ss << "Initial state. (" << a << ", " << b << ", " << c << ")";
	initial.push_back(ss.str());
	return initial;
}
	
queue<State> moves;

// does the BFS for the waterjugs
void BFS(int a, int b, int c, int goal_a, int goal_b, int goal_c){
	bool **visit=new bool*[cap_a+1];
	for(int i=0; i<cap_a+1; i++){
		visit[i]=new bool[cap_b+1];
		fill(visit[i], visit[i]+cap_b+1,false);
	}
	State initial(a, b, c);
	pours="Initial state. ";
	initial.directions.push_back(pours+initial.to_string());
	moves.push(initial);
	while(!moves.empty()){
		a=moves.front().get_a();
		b=moves.front().get_b();
		c=moves.front().get_c();
		visit[a][b]=true;
		if((a==goal_a)&&(b==goal_b)&&(c==goal_c)){
			moves.front().print_states();
			goal=true;
			break;
		}
		State front=moves.front();
		moves.pop();
		// Pour from C to A
		if(a<cap_a){
			int curr_a=a+c;
			int curr_b=b;
			if(curr_a>cap_a){
				curr_a=cap_a;
			}
			int curr_c=c-(curr_a-a);
			if(curr_b>cap_b){
				curr_b=cap_b;
			}
			stringstream ss;
			if((c-curr_c)==1){
				ss << curr_a-a;
				pours="Pour "+ss.str()+" gallon from C to A. ";
			}
			else{
				ss << curr_a-a;
				pours="Pour "+ss.str()+" gallons from C to A. ";
			}
			if(!visit[curr_a][curr_b]){
				vector<string> path=front.get_directions();
				State current(curr_a, curr_b, curr_c);
				path.push_back(pours+current.to_string());
				State paths(curr_a, curr_b, curr_c, path);
				moves.push(paths);
			}
		}
		// Pour from B to A
		if(a<cap_a){
			if(b!=0){
				int curr_c=c;
				int curr_a=a+b;
				if(curr_a>a){
					curr_a=cap_a;
				}
				int curr_b=b-(curr_a-a);
				if(curr_b<0){
					curr_b=0;
				}
				if(curr_b>cap_b){
					curr_b=cap_b;
				}
				stringstream ss;
				if((b-curr_b)==1){
					ss << b-curr_b;
					pours="Pour "+ss.str()+" gallon from B to A. ";
				}
				else{
					ss << b-curr_b;
					pours="Pour "+ss.str()+" gallons from B to A. ";
				}
				if(!visit[curr_a][curr_b]){
				vector<string> path=front.get_directions();
				State current(curr_a, curr_b, curr_c);
				path.push_back(pours+current.to_string());
				State paths(curr_a, curr_b, curr_c, path);
				moves.push(paths);
				}
			}
		}
		// Pour from C to B
		if(b<cap_b){
			int curr_b=c+b;
			int curr_a=a;
			if(curr_b>cap_b){
				curr_b=cap_b;
			}
			int curr_c=c-(curr_b-b);
			if(curr_a>cap_a){
				curr_a=cap_a;
			}
			stringstream ss;
			if((c-curr_c)==1){
				ss << curr_b-b;
				pours="Pour "+ss.str()+" gallon from C to B. ";
			}
			else{
				ss << curr_b-b;
				pours="Pour "+ss.str()+" gallons from C to B. ";
			}
			if(!visit[curr_a][curr_b]){
				vector<string> path=front.get_directions();
				State current(curr_a, curr_b, curr_c);
				path.push_back(pours+current.to_string());
				State paths(curr_a, curr_b, curr_c, path);
				moves.push(paths);
			}
		}
		// Pour from A to B
		if(b<cap_b){
			if(a!=0){
				int curr_c=c;
				int curr_b=a+b;
				int curr_a;
				if(curr_b>cap_b){
					curr_b=cap_b;
					curr_a=a-(curr_b-b);
				}
				else{
					curr_a=0;
				}
				if(curr_a<0){
					curr_a=0;
				}
				if(curr_a>cap_a){
					curr_a=cap_a;
				}
				stringstream ss;
				if((a-curr_a)==1){
					ss << curr_b-b;
					pours="Pour "+ss.str()+" gallon from A to B. ";
				}
				else{
					ss << curr_b-b;
					pours="Pour "+ss.str()+" gallons from A to B. ";
				}
				if(!visit[curr_a][curr_b]){
					vector<string> path=front.get_directions();
					State current(curr_a, curr_b, curr_c);
					path.push_back(pours+current.to_string());
					State paths(curr_a, curr_b, curr_c, path);
					moves.push(paths);
				}
			}
		}
		// Pour from B to C
		if(c<cap_c){
			if(b!=0){
				int curr_c=c+b;
				if(curr_c>cap_c){
					curr_c=cap_c;
				}
				int curr_b=c-curr_c;
				int curr_a=a;
				if(curr_b>cap_b){
					curr_b=c;
				}
				if(curr_b<0){
					curr_b=0;
				}
				if(curr_a>cap_a){
					curr_a=cap_a;
				}
				stringstream ss;
				if((b-curr_b)==1){
					ss << b-curr_b;
					pours="Pour "+ss.str()+" gallon from B to C. ";
				}
				else{
					ss << b-curr_b;
					pours="Pour "+ss.str()+" gallons from B to C. ";
				}
				if(!visit[curr_a][curr_b]){
					vector<string> path=front.get_directions();
					State current(curr_a, curr_b, curr_c);
					path.push_back(pours+current.to_string());
					State paths(curr_a, curr_b, curr_c, path);
					moves.push(paths);
				}
			}
		}
		// Pour from A to C
		if(c<cap_c){
			if(a!=0){
				int curr_c=a+c;
				if(curr_c>cap_c){
					curr_c=cap_c;
				}
				int curr_a=a-(curr_c-c);
				if(curr_a>cap_a){
					curr_a=cap_a;
				}
				if(curr_a<0){
					curr_a=0;
				}
				int curr_b=b;
				stringstream ss;
				if((a-curr_a)==1){
					ss << a-curr_a;
					pours="Pour "+ss.str()+" gallon from A to C. ";
				}
				else{
					ss <<a-curr_a;
					pours="Pour "+ss.str()+" gallons from A to C. ";
				}
				if(!visit[curr_a][curr_b]){
					vector<string> path=front.get_directions();
					State current(curr_a, curr_b, curr_c);
					path.push_back(pours+current.to_string());
					State paths(curr_a, curr_b, curr_c, path);
					moves.push(paths);
				}
			}
		}
	}
	// No solution is ever found
	if(goal==false){
		cout << "No solution." << endl;
	}
	// Clearing the heap
	for(int i=0; i<cap_a+1; i++){
		delete[] visit[i];
	}
	delete[] visit;
}
	

int main(int argc, char * const argv[]) {
	if(argc != 7){ // removes all invalid command line arguments
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	for(int i=1; i<7; i++){
		istringstream iss(argv[i]);
		int num;
		if(!(iss >> num) || (num<0) || (num==0 && i==3)){ // needs to check if the input in command line is an integer
			if((i==1) || (i==2) || (i==3)){
				cerr << "Error: Invalid capacity '" << argv[i] << "' for ";
				if(i==1){
					cerr << "jug A." << endl;
					return 1;
				}
				if(i==2){
					cerr << "jug B." << endl;
					return 1;
				}
				if(i==3){
					cerr << "jug C." << endl;
					return 1;
				}
			}
			if((i==4) || (i==5) || (i==6)){
				cerr << "Error: Invalid goal '" << argv[i] << "' for ";
				if(i==4){
					cerr << "jug A." << endl;
					return 1;
				}
				if(i==5){
					cerr << "jug B." << endl;
					return 1;
				}
				if(i==6){
					cerr << "jug C." << endl;
					return 1;
				}
			}
		}
		iss.clear();
	}
	for(int i=1; i<=3; i++){ // checks for impossible values for the goal or the capacity
		istringstream iss1(argv[i]);
		istringstream iss2(argv[i+3]);
		int num1;
		int num2;
		iss1 >> num1;
		iss2 >> num2;
		if(num1<num2){
			cerr << "Error: Goal cannot exceed capacity of ";
			if(i==1){
				cerr << "jug A." << endl;
				return 1;
			}
			if(i==2){
				cerr << "jug B." << endl;
				return 1;
			}
			if(i==3){
				cerr << "jug C." << endl;
				return 1;
			}
		}
		iss1.clear();
		iss2.clear();
	}
	istringstream isscap(argv[3]);
	istringstream iss4(argv[4]);
	istringstream iss5(argv[5]);
	istringstream iss6(argv[6]);
	int numcap;
	int num4;
	int num5;
	int num6;
	isscap >> numcap;
	iss4 >> num4;
	iss5 >> num5;
	iss6 >> num6;
	if((num4+num5+num6)!=numcap){ // Goal state cannot have more, as the initial has all the water in jug C
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	isscap.clear();
	iss4.clear();
	iss5.clear();
	iss6.clear();
	istringstream iss1(argv[1]);
	istringstream iss2(argv[2]);
	istringstream iss3(argv[3]);
	iss1 >> cap_a;
	iss2 >> cap_b;
	iss3 >> cap_c;
	istringstream issa(argv[4]);
	istringstream issb(argv[5]);
	istringstream issc(argv[6]);
	int goal_a;
	int goal_b;
	int goal_c;
	issa >> goal_a;
	issb >> goal_b;
	issc >> goal_c;
    BFS(0, 0, cap_c, goal_a, goal_b, goal_c);
	return 0;
}