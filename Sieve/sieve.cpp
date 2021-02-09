/*******************************************************************************
 * Name        : sieve.cpp
 * Author      :
 * Date        :
 * Description : Sieve of Eratosthenes
 * Pledge      :
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // Will display with cout, all the primes in order up to the max that was input
	const int max_prime_width = num_digits(max_prime_),           primes_per_row = 80 / (max_prime_width + 1);
	int row_count=0;
	for(int i=0; i<=max_prime_; i++){
		if(is_prime_[i]==true){
			if(num_primes_>primes_per_row){
				cout << setw(max_prime_width); 
			}
			cout << i;
			row_count++;
			if(row_count>=primes_per_row){
				cout << endl;
				row_count=0;
			}
			else if(i!=max_prime_){
				cout << " ";
			}
		}
	}
}

int PrimesSieve::count_num_primes() const {
    // Counts the number of primes found
	int numprimes=0;
	for(int i=2; i<=limit_; i++){
		if(is_prime_[i]==true){
			numprimes++;
		}
	}
	return numprimes;
}

void PrimesSieve::sieve() {
    // Creates a boolean array with all indexes true being prime numbers, and all indexes false not being prime numbers
	for(int n=2; n<=limit_; n++){
		is_prime_[n]=true;
	}
	for(int i=2; i<=sqrt(limit_); i++){
		if(is_prime_[i]==true){
			for(int j=0; j<=limit_; j++){
				int a=pow(i,  2);
				int b=j*i;
				is_prime_[a+b]=false;
			}
		}
	}
	num_primes_=count_num_primes();
	for (int k=limit_; k>=0; k--){
		if(is_prime_[k]==true){
			max_prime_=k;
			break;
		}
	}
}

int PrimesSieve::num_digits(int num) {
    // Finds how many didgits an integer has
    // Hint: No strings are needed. Keep dividing by 10.
	int numdigits=1;
	while(num>=10){
		num=trunc(num/10);
		numdigits++;
	}
	return numdigits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // Will display all the primes up to the set limit
	
	PrimesSieve ps(limit);
	cout << endl;
	cout << "Number of primes found: " << ps.num_primes() << endl;
	cout << "Primes up to " << limit << ":" << endl;
	ps.display_primes();
	
    return 0;
}
