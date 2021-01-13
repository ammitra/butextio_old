#include "BUTextIO.hh"

void BUTextIO::AddOutputStream() {
	streams.emplace_back(cout_stream());
}

void BUTextIO::ResetStreams() {
    for (auto &stream : streams) {
        &stream.get()->flush();
    }
}

std::unique_ptr<std::ostream> BUTextIO::cout_stream() {
    return std::make_unique<std::ostream>(std::cout.rdbuf());
}

/*
std::unique_ptr<std::ostream> BUTextIO::file_stream(const std::string& filename) {
    return std::make_unique<std::ofstream>(filename);
}

std::unique_ptr<std::ostream> BUTextIO::string_stream() {
    return std::make_unique<std::stringstream>();
}
*/