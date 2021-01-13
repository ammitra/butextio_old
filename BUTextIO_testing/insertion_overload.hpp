//https://stackoverflow.com/q/115703

template <typename T>
BUTextIO & operator<<(T const &valueToWrite) {
    for (auto &stream : streams) {
        *stream.get() << valueToWrite;
    }
    return *this;
}