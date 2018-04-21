#include "InputReader.h"

namespace game {
InputReader::InputReader() = default;

void InputReader::read_input() {
    const auto msgs = read_input_();
    messages_.add(msgs);
}
}
