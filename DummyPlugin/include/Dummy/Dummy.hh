#ifndef __DUMMY_HH__
#define __DUMMY_HH__

#include <iostream>
#include <string>

class Dummy {
    public:
        // constructor
        Dummy();
        // destructor
        ~Dummy();
        // public member functions
        float add(float x, float y);
        float subtract(float x, float y);
        float multiply(float x, float y);
    private:
    // print hello world test
    std::string helloText;
    void helloWorld(std::string const & _helloText);
};

#endif