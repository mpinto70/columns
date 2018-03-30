#include "InputReader.h"

namespace game {
InputReader::InputReader(SharedMessage messages)
      : messages_(messages) {
}

void InputReader::run() {
    while (should_process()) {
        auto msgs = get_input();
        messages_->add(msgs);
    }
}
}
