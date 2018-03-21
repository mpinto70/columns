#include "utiltest.h"

namespace mck {

std::string create_message(const std::string& file, const int line) {
    return file + "(" + std::to_string(line) + ")";
}
}
