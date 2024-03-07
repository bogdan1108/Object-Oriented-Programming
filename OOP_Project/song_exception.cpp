#include "song_exception.h"

song_exception::song_exception(const std::string& description) : errorDescription(description) {}

const char* song_exception::what() const noexcept {
    return errorDescription.c_str();
}
