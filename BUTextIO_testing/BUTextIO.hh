#ifndef __BUTEXTIO_HH__
#define __BUTEXTIO_HH__

#include <memory>
#include <vector>
#include <iostream>

class BUTextIO {
    private:
        std::vector<std::unique_ptr<std::ostream>> streams;
    public:
        //BUTextIO();
        void AddOutputStream(/* std::unique_ptr<std::ostream> */);
        void ResetStreams();
        //void Print();
        std::unique_ptr<std::ostream> cout_stream();
        std::unique_ptr<std::ostream> file_stream(const std::string& filename);
        std::unique_ptr<std::ostream> string_stream();
        // insertion operator <<
        //template <typename T>
        //BUTextIO & operator<<(T const &valueToWrite);
        template <typename T>
        BUTextIO & operator<<(T const &valueToWrite) {
            for (auto &stream : streams) {
                *stream.get() << valueToWrite;
            }
            return *this;
        }
};

//#include "insertion_overload.hpp"

#endif