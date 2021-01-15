#include <Dummy/Dummy.hh>
#include <string>
#include <iostream>

/// constructor 
Dummy::Dummy() {
    std::cout << "object is being created, constructor called" << std::endl;
}

// deconstructor 
Dummy::~Dummy() {
    std::cout << "object is being destroyed, destructor called" << std::endl;
}

float Dummy::add(float x, float y) {
    float res;
    res = x + y;
    std::cout << x << " + " << y << " = " << res << std::endl;
    return res;
}

float Dummy::subtract(float x, float y) {
    float res;
    res = x - y;
    std::cout << x << " - " << y << " = " << res << std::endl;
    return res;
}

float Dummy::multiply(float x, float y) {
    float res;
    res = x * y;
    std::cout << x << " * " << y << " = " << res << std::endl;
    return res;
}

void helloWorld(std::string const & _helloText) {
    // do nothing for now
    std::string standIn;
    standIn = _helloText;
}