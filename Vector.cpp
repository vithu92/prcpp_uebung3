#include "vector.h"
#include <iostream>
#include <memory>

using namespace std;

int main() {

	Vector<double> v1(5, 1.9);
	cout << v1 << endl;

	Vector<int> v2{ 4,3,2,1,2 };
	Vector<int> v3{ 4,3,2,1,2 };
	cout << v2 << endl;
	
	cout << v2*v3 << endl;

	

	

}