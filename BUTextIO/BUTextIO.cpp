#include <cstdarg>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

// https://stackoverflow.com/questions/15106102/how-to-use-c-stdostream-with-printf-like-formatting/52129060#52129060
// dealing with printf calls - still need to consider format-nonliteral 
struct putf_r{
        char *s;
};
putf_r putf(const char *fmt, ...){
        va_list ap;
        va_start(ap, fmt);
        putf_r a;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
        vasprintf(&a.s, fmt, ap);
#pragma GCC diagnostic pop
        va_end(ap);
        return a;
}
std::ostream& operator<<(std::ostream& os, putf_r a){
        os<<a.s;
        free(a.s);
        return os;
}

class BUTextIO {
    protected:
        std::vector<std::unique_ptr<std::ostream>> streams;
    public:
        // creating unique_ptrs to go in streams vector
        // use ostream constructor to redirect output to another stream
        std::unique_ptr<std::ostream> cout_stream() {
            return std::make_unique<std::ostream>(std::cout.rdbuf());
        }
        // do the same for files - worry about this later
        std::unique_ptr<std::ostream> file_stream(const std::string& filename) {
            return std::make_unique<std::ofstream>(filename);
        }
        // sstream redirect
        std::unique_ptr<std::ostream> string_stream() {
            return std::make_unique<std::stringstream>();
        }

        // add the unique_ptr to streams vector
        void AddOutputStream(/* const std::string & filename */) {
            streams.emplace_back(cout_stream());
            //streams.emplace_back(file_stream(filename));
            //streams.emplace_back(string_stream());
        }

        // write to all streams in the vector sequentially
        template <typename T>
        BUTextIO & operator<<(T const &valueToWrite) {
            for (auto &stream : streams) {
                *stream.get() << valueToWrite;
            }
            return *this;
        }

        void ResetStreams() {
            for (auto &stream : streams) {
                //&stream.get()->flush();
                stream->clear();
            }
        }
};

/*
 * stand-in for an apollo command taking place on the SoC
 * we want the result to pass thru BUTextIO and go to Herd and local console
 */
void DummyApolloCommand() {
    // do some stuff
    BUTextIO t;
    t.AddOutputStream(/* "blah.txt" */);
    t << "the command result is 0xDEADBEEF";
    // testing printf call
    t << putf("%3d ", 23) << putf("%a\n", 256.);
    // do we need to reset here? or in Shep?
    t.ResetStreams();
}
/*
 * this is the Shep command which calls the ApolloCommand (Shep is not running on SoC)
 * it normally produces a command status return but now we want the result, too
 */
void DummyShepCommand() {
    // currently only the command status is returned.
    std::cout << "the command successfully completed" << std::endl;

    // now, we utilize BUTextIO to retrieve cout
    // stringstream as print destination
    std::stringstream ss;
    // save old buffer & change it
    auto old = std::cout.rdbuf(ss.rdbuf());
    // all cout from the command should go to ss
    DummyApolloCommand();
    // reset buffers (here or in ApolloCommand?)
    std::cout.rdbuf(old);
    // print the command return (hopefully)
    std::cout << ss.str() << "from Shep" << std::endl;
}

int main() {
    /* * * * Testing the BUTextIO class
    BUTextIO t;
    std::cout << "BUTextIO obj instantiated" << std::endl;
    // add one cout ostream buffer to vector
    t.AddOutputStream("BUTextIO_test.txt");
    std::cout << "Output streams added to vector" << std::endl;
    // write to it
    t << "   testing testing 123 \n";
    std::cout << "streams written to" << std::endl;
    */
    DummyShepCommand();
    // return 0 implicit for main()
}