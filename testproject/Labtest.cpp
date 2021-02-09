#include <iostream>

using namespace std;

int mystery1(int a, int b) {
    int c = a - b,
        d = (c >> 7) & 1,
        mystery = a - c * d;
    return mystery;
}

void mystery2(int values[], int i, int j) {
    values[i] = values[i] ^ values[j];
    values[j] = values[i] ^ values[j];
    values[i] = values[i] ^ values[j];
}

int mystery3(int x, int y) {
    int s, c;
    s = x ^ y; //00000010 ^ 00001000 = 00001010 =10
    c = x & y; //00000010 & 00001000 = 00000000 =0
    while (c != 0) {
        c = c << 1; //=0 =00000000 
        x = s; //=10
        y = c; //=0
        s = x ^ y; //00001000 ^ 00000000=00001000 =10 
        c = x & y; //00001000 & 00000011=00000000 =0
    }
    return s;
}



int main(int argc, char* const argv[]){
	int answer=mystery1(3, 7);
	int answer2=mystery1(8, 7);
	int answer3=mystery1(2, 1);
	int answer4=mystery1(1, 2);
	int answer5=mystery3(5,7);
	int answer6=mystery3(2,8);
	cout << answer << endl;
	cout << answer2 << endl;
	cout << answer3 << endl;
	cout << answer4 << endl;
	cout << answer5 << endl;
	cout << answer6 << endl;
	return 0;
}