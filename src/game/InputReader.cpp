#include "InputReader.h"

namespace game {
InputReader::InputReader()
      : messages_(),
        running_(false),
        stop_(false) {
}

void InputReader::run() {
    running_ = true;
    stop_ = false;
    while (not stop_ && should_process()) {
        auto msgs = get_input_();
        messages_.add(msgs);
    }
    running_ = false;
}

void InputReader::stop() {
    stop_ = true;
}

Message::List InputReader::get_input() {
    return messages_.get();
}
}
