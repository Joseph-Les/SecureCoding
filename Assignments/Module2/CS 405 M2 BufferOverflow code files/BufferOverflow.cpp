// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iomanip>
#include <iostream>
#include <limits> // For std::numeric_limits

#define Max_Input 20

int main()
{
    std::cout << "Buffer Overflow Example" << std::endl;

    const std::string account_number = "OdinLes23";
    char user_input[Max_Input];

    std::cout << "Enter a value: ";

    // Use std::cin.getline to safely read input with a specified limit
    std::cin.getline(user_input, Max_Input);

    

    // Check if the input was too long and caused an overflow
    if (std::cin.fail() && !std::cin.eof()) {
        std::cin.clear(); // Clear the error flag set by cin
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        std::cout << "Error: Input exceeds maximum allowed length!" << std::endl;
    } else {
        std::cout << "You entered: " << user_input << std::endl;
    }
    
    std::cout << "Account Number = " << account_number << std::endl;
    
    std::cout << "End of Program." << std::endl;

    return 0;
}
