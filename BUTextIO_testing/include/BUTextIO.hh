#ifndef __BUTEXTIO_HH__
#define __BUTEXTIO_HH__

#include <memory>
#include <vector>
#include <iostream>

//#include "insertion_overload.hpp"

class BUTextIO {
    private:
        std::vector<std::unique_ptr<std::ostream>> streams;
    public:
        BUTextIO();
        void AddOutputStream(/*std::unique_ptr<std::ostream>*/);
        void ResetStreams();
        void Print();
        std::unique_ptr<std::ostream> cout_stream();
        std::unique_ptr<std::ostream> file_stream(const std::string& filename);
        std::unique_ptr<std::ostream> string_stream();
        template <typename T>
        BUTextIO & operator<<(T const &valueToWrite) {
            for (auto &stream : streams) {
                *stream.get() << valueToWrite;
            }
            return *this;
        }
};

#endif