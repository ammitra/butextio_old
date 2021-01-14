#include "DummyCommands.hh"

void DummyApolloCommand() {
    BUTextIO t;
    t.AddOutputStream();
    t << "the command result is 0xDEADBEEF";
    t.ResetStreams();
}

void DummyShepCommand() {
    std::cout << "the command successfully completed" << std::endl;
    std::stringstream ss;
    auto old = std::cout.rdbuf(ss.rdbuf());
    DummyApolloCommand();
    std::cout.rdbuf(old);
    std::cout << ss.str() << " from Shep" << std::endl;
}
