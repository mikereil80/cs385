/*******************************************************************************
 * Name    : complexity.cpp
 * Author  : Michael Reilly
 * Version : 1.0
 * Date    : September 13, 2019
 * Description : Is meant to find the complexity of various algorithms, and find if they should be Ο, θ, and Ω.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>

using namespace std;

class Complexity {

void function1(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += 2) {
            cout << "*";
        }
    }
}
};

int main() {
	function1 f(5);
	function1 f(3);
}