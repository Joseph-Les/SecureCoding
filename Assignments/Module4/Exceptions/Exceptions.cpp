// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <exception>
#include <stdexcept>

// Custom exception class derived from std::exception
class CustomException : public std::exception {
public:
    const char* what() const _NOEXCEPT override {
        return "Custom Exception Occurred";
    }
};

bool do_even_more_custom_application_logic() {
    // Throw any standard exception
    throw std::runtime_error("Standard runtime error");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic() {
    // Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if(do_even_more_custom_application_logic()) {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception caught in do_custom_application_logic: " << e.what() << std::endl;
    }

    // Throw a custom exception derived from std::exception
    //  and catch it explicitly in main
    throw CustomException();

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den) {
    // Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if(den == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return (num / den);
}

void do_division() noexcept {
    //  Create an exception handler to capture ONLY the exception thrown
    //  by divide.
    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Exception caught in do_division: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Exceptions Tests!" << std::endl;

    // Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.
    try {
        do_division();
        do_custom_application_logic();
    } catch (const CustomException& e) {
        std::cout << "Custom exception caught in main: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Standard exception caught in main: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception caught in main." << std::endl;
    }

    return 0;
}
