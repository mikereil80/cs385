#include <iostream>

using namespace std;

void display_array(int array[], const int length){
	cout << "[";
	if (length>0){
		cout << array[0];
	}
	for (int i=1; i<length; ++i){
		cout << ", " << array[i];
	}
	cout << "]" << endl;
}

void display_array_ptr(int array[], const int length){
	cout << "[";
	for(int *ptr=array, *end=array+length; ptr<end; ++ptr){
		if (ptr!=array){
			cout << ", ";
		}
		cout << *ptr;
	}
	cout << "]" << endl;
}

void pass_by_value(int x){
	x=10;
}

void pass_by_pointer(int *x){
	*x=10;
}

void pass_by_reference(int &x){
	x=10;
}

int main() {
	int x=5, y=6, *z=&x;
	/* *z is a pointer, in this case to an int, and & is the address of operator */
	cout << z << endl;
	cout << *z << endl;
	cout << "x = " << x << ", y = " << y << endl;
	*z=7;
	cout << "x = " << x << ", y = " << y << endl;
	z=&y;
	*z=7;
	cout << "x = " << x << ", y = " << y << endl;
	/* cout << ++z << end l; //Bad idea: We're not sure where z is at */
	/* z+=3000; // Terrible idea:: z points outside the address space of this process */
	/* *z=30; // Assigning a new value to the place z points will cause a segmentation fault */
	// use gdb to check for why code is crashing if you don't know where it went wrong in bash
	int* values = new int(y); // This chunk of memory has been allocated onto the heap
	for (int i=0; i<y; i++){
		values[i]=i;
	}
	display_array(values, y);
	display_array_ptr(values, y);
	delete [] values; // Must delete anything with new or else this will cause a memory leak
	// test with valgrind ./executable to not allow a memory leak and check, must compile first in order for it to work correctly
	pass_by_value(x); // 5, for primitives pass by value it is fine
	pass_by_pointer(&x); // 10, don't use this one
	pass_by_reference(x); // 10, use this one for objects so you don't copy everything over again
	cout << "x = " << x << endl;
	return 0;
}