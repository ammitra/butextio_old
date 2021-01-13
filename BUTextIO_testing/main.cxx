#include "BUTextIO.hh"
#include <sstream>

void DummyApolloCommand() {
    // do some stuff related to command (i.e read, svfplayer, CM power, etc)
    BUTextIO t;
    t.AddOutputStream(/* "blah.txt" */);
    // normally these would be sent to cout on-board Apollo - we want to see it in Shep
    t << "the command result is 0xDEADBEEF";
    // send characters to external destination (end of file, send to console, etc)
    t.ResetStreams();
}

void DummyShepCommand() {
    // currently only the command status is returned.
    std::cout << "the command successfully completed" << std::endl;

    // now, we utilize BUTextIO to retrieve cout
    // stringstream as print destination
    std::stringstream ss;
    // save old buffer
    auto old = std::cout.rdbuf(ss.rdbuf());
    // all cout from the ApolloCommand should go to ss
    DummyApolloCommand();
    // reset buffers
    std::cout.rdbuf(old);
    // print the command result locally (this would be seen on Shep's console - off-board)
    std::cout << ss.str() << " from Shep" << std::endl;
}

int main() {
    DummyShepCommand();
}