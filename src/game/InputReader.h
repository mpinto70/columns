#pragma once

#include "game/Messages.h"

#include <atomic>
#include <memory>

namespace game {
class InputReader {
public:
    InputReader();
    virtual ~InputReader() = default;

    void read_input();

    void clear_input() {
        messages_.clear();
    }

    Messages::List get_input() {
        return messages_.get();
    }

private:
    Messages messages_;

    virtual Messages::List read_input_() = 0;
};

using InputReaderPtr = std::unique_ptr<InputReader>;
}
