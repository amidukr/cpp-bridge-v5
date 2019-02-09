#include<iostream>
#include<myholderclass.hpp>

int main(int argc, char* argv[]) {
	
	MyHolderClass my_holder_class;
	
	std::cout << my_holder_class.GetHoldVariable() << std::endl;
	
	return 0;
}