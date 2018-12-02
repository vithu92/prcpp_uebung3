#include "vector.h"
#include <iostream>
#include <memory>

using namespace std;

int main() {

	Vector<int, 3> v1({ 2,3,4});
	cout << v1 << endl;
	Vector<int, 3> v2({ 1,2,3});
	
	cout << v1 + v2 << endl;
	cout << v1 - v2 << endl;



	

	

}