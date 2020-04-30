#include <iostream>
#include "string.h"


int main()
{
	String check("fffff");
	String check2("aaaaa");
	String sum = check + check2;
	std::cout << "first string: " << check << " second string: " << check2 << std::endl;
	std::cout << "Sum: " << sum << std::endl;
	std::cout << "Enter string :";
	String input;
	std::cin >> input;
	if (input == sum)
		std::cout << "same string" << std::endl;
	else if (input < sum)
		std::cout << "your's string < sum" << std::endl;
	else if (input > sum)
		std::cout << "your's string > sum" << std::endl;
	std::cout << "Enter number: ";
	int number;
	std::cin >> number; 
	std::cout<< std::endl << input[number] << std::endl;
	std::cout << "Enter amount of repeat" << std::endl;
	int amount;
	std::cin >> amount;
	String repeat;
	input = repeat.repeater(input, amount);
	std::cout << input << std::endl;
}