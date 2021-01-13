#include "BUTextIO.hh"

BUTextIO::AddOutputStream() {
	streams.emplace_back(cout_stream());
}

BUTextIO::ResetStreams() {
    for (auto &stream : streams) {
        &stream.get()->flush();
    }
}

BUTextIO::cout_stream() {
    return std::make_unique<std::ostream>(std::cout.rdbuf());
}

BUTextIO::file_stream(const std::string& filename) {
    return std::make_unique<std::ofstream>(filename);
}

BUTextIO::string_stream() {
    return std::make_unique<std::stringstream>();
}

