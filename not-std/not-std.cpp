// not-std.cpp : Defines the entry point for the application.
//

#include "not-std.h"
#include <typeinfo>
#include <utility>

using namespace std;

int main() {
	cout << "Hello CMake." << endl;

	cout << typeid(std::integral_constant<int, 1000>::value_type).name() << endl;
	return 0;
}
