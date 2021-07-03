#include "MyClass.h"

int main() {
	std::cout << "\ncreate class \n";
	MyClass cl;
	std::cout << "\nfill random values \n";
	cl.fillRand();
	std::cout << "\nfind max value \n";
	std::cout << cl.findMax() << '\n';
	std::cout << "\nremove repeats \n";
	cl.removeRepeats();
	std::cout << "\nreplace values which less than 0 \n";
	cl.replace();
	return 0;
}